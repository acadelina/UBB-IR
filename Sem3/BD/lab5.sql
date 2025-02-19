use MagazinHaine5
go
set ansi_nulls on
go
set quoted_identifier on
go


---FUNCTIE CARE VALIDEAVA NUMARUL DE RANDURI
create or alter function dbo.validare_NrRanduri(@rows int)
returns bit
as
begin
	declare @flag bit;
	set @flag=0;
	if @rows>=0 
		set @flag=1;
	return @flag;
end
go

---FUNCTIE CARE VALIDEAVA id-UL UNEI COMENZI
create or alter function dbo.validare_IdComanda (@CId int)
returns bit
as
begin 
	declare @start int;
	declare @end int;
	declare @flag bit;
	set @flag=0;

	select top 1 @start =Id_comanda  from Comenzi order by Id_comanda asc;
	select top 1 @end = Id_comanda from Comenzi order by Id_comanda desc;
	if @CId between @start and @end 
		set @flag=1;
	return @flag;
end
go

---FUNCTIE CARE VALIDEAVA ID-UL UNUI CLIENT
create or alter function dbo.validare_IdClient (@CId int)
returns bit
as
begin 
	declare @start int;
	declare @end int;
	declare @flag bit;
	set @flag=0;

	select top 1 @start =Cnp from Clienti order by Cnp asc;
	select top 1 @end = Cnp from Clienti order by Cnp desc;
	if @CId between @start and @end 
		set @flag=1;
	return @flag;
end
go

---FUNCTIE CARE VALIDEAVA ID-UL UNEI CATEGORII
create or alter function dbo.validare_IdCategorie (@CId int)
returns bit
as
begin 
	declare @start int;
	declare @end int;
	declare @flag bit;
	set @flag=0;

	select top 1 @start =Id_categorie from Categorii order by Id_categorie asc;
	select top 1 @end = Id_categorie from Categorii order by Id_categorie desc;
	if @CId between @start and @end 
		set @flag=1;
	return @flag;
end
go


---FUNCTIE CARE VALIDEAVA ID-UL UNUI PRODUS
create or alter function dbo.validare_IdProdus (@PId int)
returns bit
as
begin 
	declare @start int;
	declare @end int;
	declare @flag bit;
	set @flag=0;

	select top 1 @start =Id_produs  from Produse order by Id_produs asc;
	select top 1 @end = Id_produs from Produse order by Id_produs desc;
	if @PId between @start and @end 
		set @flag=1;
	return @flag;
end
go


create or alter procedure verificare_ComenziProduse
		@flag bit output,
		@mesaj varchar(30) output,
		@Cantitate int,
		@Pret int,
		@rows int
as
begin
	declare @suma int;
	set @flag=0;
	set @mesaj='';
	set @suma=0;
	begin
		if @Cantitate <= 0
			begin
				set @mesaj=@mesaj+'Cantitate ';
				set @suma=@suma+1;
			end
		if @Pret<0
			begin
				set @mesaj=@mesaj+'Pret ';
				set @suma=@suma+1;
			end
		if dbo.validare_NrRanduri(@rows)=0
			begin
				set @mesaj=@mesaj+'Randuri ';
				set @suma=@suma+1;
			end
	end
	if @suma=0
		set @flag=1;
end
go


create or alter procedure verificare_Comenzi
	@flag bit output,
	@mesaj varchar(30) output,
	@data varchar(15),
	@pret int,
	@client int,
	@rows int
as
begin
	declare @suma int;
	set @flag=0;
	set @mesaj='';
	set @suma=0;
	begin
		if ISDATE(@data)=0
			begin
				set @mesaj=@mesaj+'Data ';
				set @suma=@suma+1;
			end
		if @pret<0
			begin
				set @mesaj=@mesaj+'Pret ';
				set @suma=@suma+1;
			end
		if dbo.validare_IdClient(@client)=0
			begin
				set @mesaj=@mesaj+'Client ';
				set @suma=@suma+1;
			end
		if dbo.validare_NrRanduri(@rows)=0
			begin
				set @mesaj=@mesaj+'Randuri ';
				set @suma=@suma+1;
			end
	end
	if @suma=0
		set @flag=1;
end
go

create or alter procedure verificare_Client
	@flag bit output,
	@mesaj varchar(30) output,
	@nume varchar(50),
	@varsta int,
	@rows int
as
begin
	declare @suma int;
	set @flag=0;
	set @mesaj='';
	set @suma=0;
	begin
		if LEN(@nume)<=0
			begin
				set @mesaj=@mesaj+'Nume ';
				set @suma=@suma+1;
			end
		if @varsta<=0
			begin
				set @mesaj=@mesaj+'Varsta ';
				set @suma=@suma+1;
			end
		if dbo.validare_NrRanduri(@rows)=0
			begin
				set @mesaj=@mesaj+'Randuri ';
				set @suma=@suma+1;
			end
	end
	if @suma=0
		set @flag=1
end
go

create or alter procedure verificare_Produs
	@flag int output,
	@mesaj varchar(30) output,
	@denumire varchar(30),
	@stock int,
	@pret int,
	@categorie int,
	@rows int
as 
begin
	declare @suma int;
	set @flag=0;
	set @mesaj='';
	set @suma=0;
	begin
		
		if @stock<0
			begin
				set @mesaj=@mesaj+'Stock ';
				set @suma=@suma+1;
			end
		if @pret<0
			begin
				set @mesaj=@mesaj+'Pret ';
				set @suma=@suma+1;
			end
		if dbo.validare_IdCategorie(@categorie)=0
			begin
				set @mesaj=@mesaj+'IdCategorie ';
				set @suma=@suma+1;
			end
		if dbo.validare_NrRanduri(@rows)=0
			begin
				set @mesaj=@mesaj+'Randuri ';
				set @suma=@suma+1;
			end
	end
	if @suma=0
		set @flag=1
end
go


create or alter procedure verificare_Categorie
	@flag int output,
	@mesaj varchar(30) output,
	@rows int
as
begin
	declare @suma int;
	set @mesaj='';
	set @suma=0;
	begin
		set @flag=1
		if dbo.validare_NrRanduri(@rows)=0
			begin
				set @mesaj=@mesaj+'Randuri ';
				set @suma=@suma+1;
				set @flag=0;
			end
	end
	
end
go


----Operatii CRUD pe tabela Categorii---


create or alter procedure CRUD_Categorii
	@titlu varchar(30),
	@descriere varchar(30),
	@rows int
as
begin
	set nocount on;

	declare @i int;
	declare @cid int;
	declare @flag bit;
	declare @mesaj varchar(30)


	set @cid=0;

	select top 1 @cid=Id_categorie from Categorii order by Id_categorie desc
	set @i=1;

	exec verificare_Categorie @flag output, @mesaj output, @rows

	if @flag=0
		print 'Eroare la datele de intrare: '+@mesaj
	else
		begin
			--INSERT--
			while @i<=@rows
			begin
				set @cid=@cid+1
				insert into Categorii values (@cid,@titlu,@descriere)
				set @i=@i+1
			end

			--SELECT--
			select * from Categorii

			--UPDATE--
			update Categorii set Titlu='Accesorii' where Id_categorie>5
			select * from Categorii
			--DELETE--
			DELETE Categorii where Titlu='Accesorii';

			select * from Categorii
			print 'S-au efectuat operatiile CRUD pe tabela categorii'
		end
end
go



----Operatii CRUD pe tabela Produse---


create or alter procedure CRUD_Produse
	@denumire varchar(30),
	@stock int,
	@pret int,
	@categorie int,
	@rows int
as
begin
	set nocount on;

	declare @i int;
	declare @pid int;
	declare @flag bit;
	declare @mesaj varchar(30)


	set @pid=0;

	select top 1 @pid=Id_produs from Produse order by Id_produs desc
	set @i=1;

	exec verificare_Produs @flag output, @mesaj output,@denumire, @stock, @pret,@categorie,@rows

	if @flag=0
		print 'Eroare la datele de intrare: '+@mesaj
	else
		begin
			--INSERT--
			while @i<=@rows
			begin
				set @pid=@pid+1
				insert into Produse values (@pid,@denumire,@stock,@pret,@categorie)
				set @i=@i+1
			end

			--SELECT--
			select * from Produse

			--UPDATE--
			update Produse set Denumire='Bluza' where Id_produs>5

			--DELETE--
			DELETE Produse where Denumire='Bluza';

			print 'S-au efectuat operatiile CRUD pe tabela categorii'
		end
end
go



----Operatii CRUD pe tabela Clienti---


create or alter procedure CRUD_Clienti
	@nume varchar(30),
	@varsta int,
	@rows int
as
begin
	set nocount on;

	declare @i int;
	declare @cid int;
	declare @flag bit;
	declare @mesaj varchar(30)


	set @cid=0;

	select top 1 @cid=Cnp from Clienti order by Cnp desc
	set @i=1;

	exec verificare_Client @flag output, @mesaj output,@nume, @varsta,@rows

	if @flag=0
		print 'Eroare la datele de intrare: '+@mesaj
	else
		begin
			--INSERT--
			while @i<=@rows
			begin
				set @cid=@cid+1
				insert into Clienti values (@cid,@nume,@varsta)
				set @i=@i+1
			end

			--SELECT--
			select * from Clienti

			--UPDATE--
			update Clienti set Nume='Ana' where cnp>5

			--DELETE--
			DELETE Clienti where Nume='Ana';

			print 'S-au efectuat operatiile CRUD pe tabela categorii'
		end
end
go



----Operatii CRUD pe tabela Comenzi---


create or alter procedure CRUD_Comenzi
	@data varchar(30),
	@pret int,
	@client int,
	@rows int
as
begin
	set nocount on;

	declare @i int;
	declare @cid int;
	declare @flag bit;
	declare @mesaj varchar(30)


	set @cid=0;

	select top 1 @cid= Id_comanda  from Comenzi order by Id_comanda desc
	set @i=1;

	exec verificare_Comenzi @flag output, @mesaj output,@data, @pret,@client,@rows

	if @flag=0
		print 'Eroare la datele de intrare: '+@mesaj
	else
		begin
			--INSERT--
			while @i<=@rows
			begin
				set @cid=@cid+1
				insert into Comenzi values (@cid,@data,@pret,@client)
				set @i=@i+1
			end

			--SELECT--
			select * from Comenzi

			--UPDATE--
			update Comenzi set Pret_total=200 where Id_comanda>5
			select * from Comenzi
			--DELETE--
			DELETE Comenzi where Pret_total=200;
			select * from Comenzi

			print 'S-au efectuat operatiile CRUD pe tabela categorii'
		end
end
go



----Operatii CRUD pe tabela ComenziProduse---


create or alter procedure CRUD_ComenziProduse
	@idComanda int,
	@idProdus int,
	@pret int,
	@cantitate int,
	@rows int
as
begin
	set nocount on;

	declare @i int;
	declare @cid int;
	declare @pid int;
	declare @flag bit;
	declare @mesaj varchar(30)


	set @cid=0;

	select top 1 @cid=Id from Comenzi_Produse order by Id desc
	
	set @i=1;

	exec verificare_ComenziProduse @flag output, @mesaj output, @cantitate,@pret,@rows

	if @flag=0
		print 'Eroare la datele de intrare: '+@mesaj
	else
		begin
			--INSERT--
			while @i<=@rows
			begin
				set @cid=@cid+1
				insert into Comenzi_Produse values (@cid,@idComanda,@idProdus,@cantitate,@pret)
				set @i=@i+1
			end

			--SELECT--
			select * from Comenzi_Produse

			--UPDATE--
			update Comenzi_Produse set Pret=200 where cid>4
			select * from Comenzi_Produse
			--DELETE--
			DELETE Comenzi_Produse where Pret=200;
			
			select * from Comenzi_Produse

			print 'S-au efectuat operatiile CRUD pe tabela categorii'
		end
end
go

create or alter procedure CRUD_main
as
begin
	exec CRUD_Categorii 'Categorie','desc',6
	exec CRUD_Produse 'Produs',10,10,1,6
	exec CRUD_Clienti 'ION',18,6
	exec CRUD_Comenzi '1999-04-11',10,1,6
	exec CRUD_ComenziProduse 1,1,34,1,6
end
go

exec CRUD_Categorii 'Categorie','desc',-5


select * from Clienti
exec CRUD_main

	
