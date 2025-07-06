create or alter function dbo.validare_material (@denumire varchar(50))
returns bit
as
begin 
	declare @flag bit
	set @flag = 1

	if @denumire is null or @denumire =''
		set @flag=0;

	if exists (select 1 from Materiale where Denumire = @denumire)
        set @flag = 0;
	return @flag;
end
go

create or alter function dbo.validare_produs (@nume_produs varchar(100))
returns bit
as
begin 
	declare @flag bit
	set @flag = 1

	if @nume_produs is null or @nume_produs=''
		set @flag=0;

	if (select count(*) from Produse where Denumire=@nume_produs )=0
		set @flag=0;
	return @flag;
end
go

create table LogActiuni (
    Id_log int identity(1,1) primary key,
    DataActiune datetime default getdate(),
    Actiune varchar(255),
    Status varchar(20),
    Mesaj text
);


create or alter procedure AddFiltreMateriale2 
    @material varchar(50),
    @nume_produs varchar(100)
as 
begin
    set nocount on;

    declare @id_filtru int;
    declare @id_material int;
    declare @ok_filtru bit = 0;
    declare @ok_material bit = 0;

    -- Incerc sa inserez in Filtre_produse
    begin try
        if dbo.validare_produs(@nume_produs) = 1
        begin
			declare @id_produs int;
			select @id_produs = Id_produs
			from Produse
			where Denumire = @nume_produs;
            begin tran;
                insert into Filtre_produse(Id_produs) values (@id_produs);
            commit tran;
            print 'Filtru adaugat';
			insert into LogActiuni(Actiune, Status, Mesaj)
            values ('Inserare Filtru', 'Succes', 'Filtru adaugat cu succes pentru produsul: ' + @nume_produs);
            set @ok_filtru = 1;
        end
        else
        begin
            print 'Id_produs invalid. Filtru nu a fost adaugat.';
			insert into LogActiuni(Actiune, Status, Mesaj)
            values ('Validare Produs', 'Eroare', 'Produs invalid: ' + @nume_produs);
        end
    end try
    begin catch
        if @@TRANCOUNT > 0 rollback tran;
        print 'Eroare la adaugarea filtrului: ' + ERROR_MESSAGE();
		 insert into LogActiuni(Actiune, Status, Mesaj)
        values ('Inserare Filtru', 'Eroare', 'eroare la inserarea filru');
    end catch

    -- Incerc sa inserez in Materiale
    begin try
        if dbo.validare_material(@material) = 1
        begin
            begin tran;
                insert into Materiale(Denumire) values (@material);
            commit tran;
            print 'Material adaugat';
            set @ok_material = 1;
        end
        else
        begin
            print 'Denumire material invalida. Materialul nu a fost adaugat.';

        end
    end try
    begin catch
        if @@TRANCOUNT > 0 rollback tran;
        print 'Eroare la adaugarea materialului: ' + ERROR_MESSAGE();
    end catch

    -- Leag filtrul de material doar daca ambele s-au adaugat
    if @ok_filtru = 1 and @ok_material = 1
    begin
        begin try
            begin tran;
                select top 1 @id_filtru = Id_filtru from Filtre_produse order by Id_filtru desc;
                select top 1 @id_material = Id_material from Materiale order by Id_material desc;

                insert into Filtre_Materiale(Id_filtru, Id_material)
                values (@id_filtru, @id_material);
            commit tran;
            print 'Filtru-Material legatura adaugata';
			insert into LogActiuni(Actiune, Status, Mesaj)
            values ('Inserare Material', 'Succes', 'Material adaugat: ' + @material);

        end try
        begin catch
            if @@TRANCOUNT > 0 rollback tran;
            print 'Eroare la adaugarea legaturii Filtru-Material: ' + ERROR_MESSAGE();
			insert into LogActiuni(Actiune, Status, Mesaj)
            values ('Validare Material', 'Eroare', 'Material invalid: ' + @material);
        end catch
    end
    else
    begin
        print 'Nu s-au putut adauga ambele entitati, deci nu putem crea legatura.';
		insert into LogActiuni(Actiune, Status, Mesaj)
        values ('Inserare Material', 'Eroare', 'nu s-a putut adauga filtrul');
    end
end
go


delete from Filtre_Materiale where Id_filtru>=13
delete from Materiale where Denumire='material1'
delete from Filtre_produse where Id_filtru>13

delete from Produse where Id_produs=19

select * from Produse
select * from Filtre_produse
select * from Materiale
select * from Filtre_Materiale
execute AddFiltreMateriale2 'material1','Sacou'; 
go
select * from Filtre_produse
select * from Materiale
select * from Filtre_Materiale
select top 10 * from LogActiuni order by DataActiune desc;


select * from Filtre_produse
select * from Materiale
select * from Filtre_Materiale
execute AddFiltreMateriale2 '','Sandale'; 


select * from Filtre_produse
select * from Materiale
select * from Filtre_Materiale
select top 10 * from LogActiuni order by DataActiune desc;

select * from Filtre_produse
select * from Materiale
select * from Filtre_Materiale
execute AddFiltreMateriale2 'material2','produs'; 
select * from Filtre_produse
select * from Materiale
select * from Filtre_Materiale
select top 10 * from LogActiuni order by DataActiune desc;

