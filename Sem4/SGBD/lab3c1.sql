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
	

	if @nume_produs is null or @nume_produs=''
		return 0;

	if (select count(*) from Produse where Denumire=@nume_produs )=0
		return 0;

	declare @id_produs int;
	select @id_produs = Id_produs
	from Produse
	where Denumire = @nume_produs;

	if(select count(*) from Filtre_produse where Id_produs=@id_produs)>0
		return 0;
		
	return 1;
end
go

create table LogActiuni (
    Id_log int identity(1,1) primary key,
    DataActiune datetime default getdate(),
    Actiune varchar(255),
    Status varchar(20),
    Mesaj text
);


create or alter procedure AddFiltreMateriale 
	@material varchar(50),@nume_produs varchar(100) as 
	begin
begin tran
	begin try
		if dbo.validare_material(@material) <>1
			begin
				print 'material'
				insert into LogActiuni(Actiune, Status, Mesaj)
				values ('Validare Material', 'Eroare', 'Material invalid: ' + isnull(@material, 'NULL'));
				raiserror('Material invalid',14,1);
			end
		if dbo.validare_produs(@nume_produs) <>1
			begin
				print 'nume produs'
				insert into LogActiuni(Actiune, Status, Mesaj)
				values ('Validare Produs', 'Eroare', 'Produs invalid: ' + isnull(@nume_produs, 'NULL'));
				raiserror('Nume produs invalid',14,1);
			end

		insert into Materiale (Denumire) values (@material);
		print 'Material adaugat'
		insert into LogActiuni(Actiune, Status, Mesaj)
        values ('Inserare Material', 'Succes', 'Material adaugat: ' + @material);

		declare @id_produs int;
		select @id_produs = Id_produs
		from Produse
		where Denumire = @nume_produs;
		insert into Filtre_produse(Id_produs) values (@id_produs);
		print 'Filtru adaugat'
		insert into LogActiuni(Actiune, Status, Mesaj)
        values ('Inserare Filtru', 'Succes', 'Filtru adaugat pentru produsul: ' + @nume_produs);

		declare @id_filtru int;
		declare @id_material int;

		select top 1 @id_filtru= F.Id_filtru
		from Filtre_produse as F
		order by F.Id_filtru desc

		select top 1 @id_material=M.Id_material
		from Materiale as M
		order by M.Id_material desc

		insert into Filtre_Materiale values (@id_filtru,@id_material)
		insert into LogActiuni(Actiune, Status, Mesaj)
        values ('Inserare Legatura', 'Succes', 'Legatura creata intre Id_filtru=' + cast(@id_filtru as varchar) + ' si Id_material=' + cast(@id_material as varchar));

		commit tran
		select 'Transaction commited'
	end try
	begin catch
		rollback tran
		declare @msg nvarchar(4000) = ERROR_MESSAGE();
        print @msg;
        insert into LogActiuni(Actiune, Status, Mesaj)
        values ('Transactie', 'Eroare', @msg);
		select 'Transaction rollbacked '
	end catch
end

delete from Filtre_Materiale where Id_filtru>100
delete from Filtre_produse where Id_produs=7

select * from Produse
select * from Filtre_produse
select * from Materiale
select * from Filtre_Materiale
execute AddFiltreMateriale 'material3','Camasa'; 

select * from Filtre_produse
select * from Materiale
select * from Filtre_Materiale
select top 10 * from LogActiuni order by DataActiune desc;
execute AddFiltreMateriale '','Geaca de piele'; 

select * from Filtre_produse
select * from Materiale
select * from Filtre_Materiale
select top 10 * from LogActiuni order by DataActiune desc;
execute AddFiltreMateriale 'material4','produs'; 
select * from Filtre_produse
select * from Materiale
select * from Filtre_Materiale
select top 10 * from LogActiuni order by DataActiune desc;