Create database AdministrareSpital
go
use AdministrareSpital


CREATE TABLE Departamente
(Id INT PRIMARY KEY IDENTITY,
Nume varchar(50),
)


CREATE TABLE Doctor
(Id INT PRIMARY KEY IDENTITY,
Nume varchar(50),
DataN date,
IdDepartament INT FOREIGN KEY REFERENCES Departamente(Id)
)


CREATE TABLE Pacient
(Id INT PRIMARY KEY IDENTITY,
Nume varchar(50),
DataN date
)


CREATE TABLE PacientDoctor
(Id INT PRIMARY KEY IDENTITY,
IdPacient INT FOREIGN KEY REFERENCES Pacient(Id),
IdDoctor INT FOREIGN KEY REFERENCES Doctor(Id)
)

CREATE TABLE Boli
(Id INT PRIMARY KEY IDENTITY,
Nume varchar(50),
)


CREATE TABLE PacientBoli
(Id INT PRIMARY KEY IDENTITY,
IdPacient INT FOREIGN KEY REFERENCES Pacient(Id),
IdBoala INT FOREIGN KEY REFERENCES Boli(Id)
)


CREATE TABLE Tratamente
(Id INT PRIMARY KEY IDENTITY,
Denumire varchar(50),
)


CREATE TABLE BoliTratamente
(Id INT PRIMARY KEY IDENTITY,
IdBoala INT FOREIGN KEY REFERENCES Boli(Id),
IdTratament INT FOREIGN KEY REFERENCES Tratamente(Id)
)


---o interogare SQL care sa aiseze departamentele a caror denumire contine "pediatrie"
SELECT * 
FROM Departamente
WHERE Nume LIKE '%pediatrie%';

--Creați o functie care returneaza cate boli de care sufera mai mult de 3 pacienti exista.
CREATE OR ALTER FUNCTION Boli3()
RETURNS TABLE
AS
RETURN
(
    SELECT 
        b.Nume,
        COUNT(pb.IdPacient) AS pc
    FROM Boli b
    JOIN PacientBoli pb ON b.Id = pb.IdBoala
    GROUP BY b.Nume
    HAVING COUNT(pb.IdPacient) >3
);

SELECT * FROM Boli3();

CREATE OR ALTER VIEW tratamenteA AS
SELECT 
    t.Denumire,
	COUNT(tb.IdBoala) AS NRBoli
FROM Tratamente t
JOIN BoliTratamente tb ON t.Id=tb.IdTratament
GROUP BY t.Denumire
HAVING COUNT(tb.IdBoala)>2

SELECT * FROM tratamenteA;