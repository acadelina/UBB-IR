Create database AdministrareInchirieriFilme
go
use AdministrareInchirieriFilme
go

CREATE TABLE TipFilm
(Id INT PRIMARY KEY IDENTITY,
Titlu varchar(50)
)


CREATE TABLE Regizori
(Id INT PRIMARY KEY IDENTITY,
Nume varchar(50),
datan date
)

CREATE TABLE Filme
(Id INT PRIMARY KEY IDENTITY,
Titlu varchar(50),
Durata INT NOT NULL,
An int,
pret int,
IdRegizor INT FOREIGN KEY REFERENCES Regizori(Id),
IdTip INT FOREIGN KEY REFERENCES TipFilm(Id)
)
 
 
CREATE TABLE Tari
(Id INT PRIMARY KEY IDENTITY,
Nume varchar(50) UNIQUE NOT NULL
)


CREATE TABLE Actori
(Id INT PRIMARY KEY IDENTITY,
Nume varchar(50) NOT NULL UNIQUE,
IdTara INT FOREIGN KEY REFERENCES Tari(Id))



CREATE TABLE ActoriFilme
(Id INT PRIMARY KEY IDENTITY,
IdFilm INT FOREIGN KEY REFERENCES Filme(Id),
IdActor INT FOREIGN KEY REFERENCES Actori(Id)
)


CREATE TABLE Clienti
(Id INT PRIMARY KEY IDENTITY,
Nume varchar(50)
)



CREATE TABLE Inchirieri
(Id INT PRIMARY KEY IDENTITY,
IdFilm INT FOREIGN KEY REFERENCES Filme(Id),
IdClient INT FOREIGN KEY REFERENCES Clienti(Id),
IntervalIn datetime,
IntervalSf datetime
)



INSERT INTO Tari (Nume) VALUES 
('România'),
('SUA'),
('Marea Britanie'),
('Franța');

INSERT INTO Regizori (Nume, datan) VALUES 
('Christopher Nolan', '1970-07-30'),
('Quentin Tarantino', '1963-03-27'),
('James Cameron', '1954-08-16'),
('Steven Spielberg', '1946-12-18');


INSERT INTO TipFilm (Titlu) VALUES 
('Drama'),
('Comedie'),
('Actiune'),
('SF');


INSERT INTO Filme (Titlu, Durata, An, pret, IdRegizor, IdTip) VALUES
('Inception', 148, 2010, 25, 1, 4),
('Pulp Fiction', 154, 1994, 20, 2, 1),
('Avatar', 162, 2009, 30, 3, 4),
('Jurassic Park', 127, 1993, 15, 4, 3),
('Django Unchained', 165, 2012, 22, 2, 3);

-- 5. Populăm tabelul Actori
INSERT INTO Actori (Nume, IdTara) VALUES 
('Leonardo DiCaprio', 2),
('Samuel L. Jackson', 2),
('Kate Winslet', 2),
('Jeff Goldblum', 3),
('Jamie Foxx', 2);

-- 6. Populăm tabelul FilmeActori
INSERT INTO ActoriFilme(IdFilm, IdActor) VALUES 
(1, 1), -- Leonardo DiCaprio în Inception
(2, 2), -- Samuel L. Jackson în Pulp Fiction
(3, 1), -- Leonardo DiCaprio în Avatar
(3, 3), -- Kate Winslet în Avatar
(4, 4), -- Jeff Goldblum în Jurassic Park
(5, 5), -- Jamie Foxx în Django Unchained
(5, 2); -- Samuel L. Jackson în Django Unchained

-- 7. Populăm tabelul Clienti
INSERT INTO Clienti (Nume) VALUES 
('Andrei Popescu'),
('Maria Ionescu'),
('John Doe'),
('Emma Watson');

-- 8. Populăm tabelul Inchirieri
INSERT INTO Inchirieri (IdClient, IdFilm, IntervalIn, IntervalSf) VALUES 
(1, 1, '2023-01-10', '2023-01-15'), -- Andrei Popescu închiriază Inception
(2, 2, '2023-01-12', '2023-01-18'), -- Maria Ionescu închiriază Pulp Fiction
(3, 3, '2021-11-01', '2021-11-10'), -- John Doe închiriază Avatar
(4, 4, '2021-12-01', '2021-12-07'), -- Emma Watson închiriază Jurassic Park
(1, 5, '2022-05-01', '2022-05-10'); -- Andrei Popescu închiriază Django Unchained



INSERT INTO Filme (Titlu, Durata, An, pret, IdRegizor, IdTip) VALUES
('Inception poveste', 148, 2010, 25, 1, 4)

SELECT f.Titlu as NumeFilm
FROM Filme f
WHERE f.Titlu LIKE '%poveste%'



CREATE OR ALTER VIEW ActoriA AS
SELECT 
    a.Nume AS ActorName,
	COUNT(DISTINCT af.IdFilm) AS Countf
FROM Actori a
JOIN ActoriFilme af ON a.Id = af.IdActor
GROUP BY a.Id,a.Nume
HAVING COUNT(DISTINCT af.IdFilm)>3;

select * from ActoriA



CREATE or ALTER PROCEDURE FilmeNeinchiriate
AS
BEGIN
	SELECT *
	FROM Filme f
	WHERE NOT EXISTS(
		SELECT 1
		FROM Inchirieri i
		WHERE i.IdFilm=f.Id
		);
END

exec FilmeNeinchiriate

CREATE OR ALTER FUNCTION NrClienti()
RETURNS 
INT
AS
BEGIN
RETURN
(
    SELECT 
        COUNT(DISTINCT i.Id) AS Countf
	From Filme f
    JOIN Inchirieri i ON f.Id= i.IdFilm 
	WHERE 
		f.pret>10 and i.IntervalIn>='2021-01-01' and i.IntervalSf<'2022-01-01'
    
)END;

select dbo.NrClienti() as NumarClienti