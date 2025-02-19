Create database AdministrarePolitie
go
use AdministrarePolitie
go


CREATE TABLE Sectii
(Id INT PRIMARY KEY IDENTITY,
Denumire varchar(50),
Adresa varchar(50)
)


CREATE TABLE Grade
(Id INT PRIMARY KEY IDENTITY,
Denumire varchar(50)
)


CREATE TABLE Sectoare
(Id INT PRIMARY KEY IDENTITY,
Denumire varchar(50))


CREATE TABLE Politisti
(Id INT PRIMARY KEY IDENTITY,
Nume varchar(50),
Prenume varchar(50),
IdSectie INT FOREIGN KEY REFERENCES Sectii(Id),
IdGrad INT FOREIGN KEY REFERENCES Grade(Id),
)


CREATE TABLE Programari
(Id INT PRIMARY KEY IDENTITY,
IdPolitist INT FOREIGN KEY REFERENCES Politisti(Id),
IdSector INT FOREIGN KEY REFERENCES Sectoare(Id),
Intrare datetime NOT NULL,
Iesire datetime NOT NULL
)



insert into Sectoare values('sector 1')
insert into Sectoare values('sector 2')
insert into Sectoare values('sector 3')
insert into Sectoare values('sector 4')
insert into Sectoare values('sector 5')

insert into Grade values('officer')
insert into Grade values('sheriff')
insert into Grade values('detective')
insert into Grade values('swat')

insert into Sectii values('station 1', 'asdsad')
insert into Sectii values('station 2', 'asdsad')
insert into Sectii values('station 3', 'asdsad')
insert into Sectii values('station 4', 'asdsad')
insert into Sectii values('station 5', 'asdsad')

insert into Politisti values('Bob', 'Bob',1,1)
insert into Politisti values('George', 'Bobert', 2,2)
insert into Politisti values('John', 'Wick', 3,3)
insert into Politisti values('Bobish', 'Zack', 4,4)

insert into Programari values(1,1,'2022-09-09 00:00:00', '2022-09-09 12:00:00')
insert into Programari values(2,2,'2022-05-05 10:30:00', '2022-05-05 12:00:00')
insert into Programari values(3,3,'2022-09-09 00:00:00', '2022-09-09 12:00:00')
insert into Programari values(4,4,'2022-10-10 00:00:00', '2022-10-10 04:30:00')



---PROCEDURA STOCATA CARE PRIMESTE UB POLITIST, UN SECTOR, O DATA SI ORA DE INTRARE, O DATA SI ORA DE IESIRE 
---DACA PROGRAMAREA EXISTA DEJA EA SE ACTUALIZEAZA ORELE, DACA NU SE ADAUGA PROGRAMAREA

CREATE or ALTER PROCEDURE AdaugaProgramare
(
	@politistId INT,
	@sectorId INT,
	@intrare datetime,
	@iesire datetime
	)
AS 
BEGIN
	IF EXISTS(
		select 1 from Programari
		where IdPolitist=@politistId and IdSector=@sectorId AND Intrare=@intrare
	)
	BEGIN
		UPDATE Programari
		SET Intrare=@intrare, Iesire=@iesire
		WHERE IdPolitist=@politistId and IdSector=@sectorId
	END
	ELSE
		BEGIN
		INSERT INTO Programari(IdPolitist,IdSector,Intrare,Iesire)
		VALUES (@politistId,@sectorId,@intrare,@iesire)
		END
END
		
exec AdaugaProgramare  1, 3, '2022-10-10 00:00:00', '2022-10-10 04:30:00'


---	CREATI UN  VIEW CARE AFISEAZA O LISTA A POLITISTILOR,ORDONATI ALFABETIC DUPA SECTIE SI NUMELE POLITISTULUI CARE SA PREZINTE NR DE ORE TOTAL DE MUNCA PENTRU LUNA IANUARIE A ANULUI CURENT
create or alter view ex3 as
	select top (select count(*) from Programari) pr.IdPolitist, pl.Nume, pl.Prenume, s.Denumire, sum(DATEDIFF(hour, Intrare, Iesire)) as NrOreLucrate
	from Programari pr inner join Politisti pl on pr.idPolitist=pl.id
	inner join Sectii s on pl.IdSectie=s.id
	where month(Intrare)=1 and year(Intrare)=year(getdate())
	group by pr.IdPolitist, Nume, Prenume, s.Denumire
	order by s.Denumire, pl.Nume, pl.Prenume asc


insert into Programari values(1,5,'2025-01-01 00:00:00', '2025-01-01 04:30:00')
insert into Programari values(1,1,'2025-01-01 00:00:00', '2025-01-01 04:30:00')
insert into Programari values(2,1,'2025-01-01 00:00:00', '2025-01-01 04:30:00')
insert into Programari values(2,2,'2025-01-01 00:00:00', '2025-01-01 04:30:00')
insert into Programari values(2,3,'2025-01-01 00:00:00', '2025-01-01 04:30:00')

select * from ex3

---CREATI O FUNCTIE CARE AFISEAZA LISTA POLITISTILOR CARE AU MAI MULTE PROGRAMARI LA O ANUMITA ORA SI DATA

CREATE OR ALTER FUNCTION ex4(@data DATETIME)
	returns table
AS
	RETURN
		SELECT 
			p.id, p.Nume, p.Prenume, COUNT(*) AS NumarProgramari
		FROM Programari pr
		JOIN Politisti p ON pr.IdPolitist=p.Id
		WHERE pr.Intrare = @data
		GROUP BY p.Id, p.Nume, p.Prenume
		HAVING COUNT(*)>1


select * from [dbo].ex4('2025-01-01 00:00:00')
