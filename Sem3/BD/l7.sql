Create database AdministrareCinema
go
use AdministrareCinema
go




CREATE TABLE Company
(Id INT PRIMARY KEY IDENTITY,
Nume varchar(50)
)


CREATE TABLE Director
(Id INT PRIMARY KEY IDENTITY,
Nume varchar(50),
Premii INT
)

CREATE TABLE Filme
(Id INT PRIMARY KEY IDENTITY,
Nume varchar(50),
Datar datetime,
IdCompanie INT FOREIGN KEY REFERENCES Company(Id),
IdDirector INT FOREIGN KEY REFERENCES Director(Id)
)



CREATE TABLE Productie
(Id INT PRIMARY KEY IDENTITY,
Titlu varchar(50),
IdFilm INT FOREIGN KEY REFERENCES Filme(Id)
)


CREATE TABLE Actori
(Id INT PRIMARY KEY IDENTITY,
Nume varchar(50),
Ranking int
)


CREATE TABLE ProductieActori
(Id INT PRIMARY KEY IDENTITY,
Entrym datetime,
IdActor INT FOREIGN KEY REFERENCES Actori(Id),
IdProductie INT FOREIGN KEY REFERENCES Productie(Id)
)


INSERT INTO Company (Nume)
VALUES ('Warner Bros'), 
       ('Universal Pictures'),
       ('Paramount Pictures');


INSERT INTO Director (Nume, Premii)
VALUES ('Christopher Nolan', 10),
       ('Steven Spielberg', 12),
       ('Quentin Tarantino', 8);


INSERT INTO Filme (Nume, Datar, IdCompanie, IdDirector)
VALUES ('Inception', '2010-07-16', 1, 1),  -- Warner Bros, Nolan
       ('Jurassic Park', '1993-06-11', 2, 2),  -- Universal, Spielberg
       ('Pulp Fiction', '1994-10-14', 3, 3);  -- Paramount, Tarantino


INSERT INTO Productie (Titlu, IdFilm)
VALUES ('Inception Production', 1),
       ('Jurassic Park Production', 2),
       ('Pulp Fiction Production', 3);


INSERT INTO Actori (Nume, Ranking)
VALUES ('Leonardo DiCaprio', 1),
       ('Samuel L. Jackson', 2),
       ('Jeff Goldblum', 3),
       ('Uma Thurman', 4);


INSERT INTO ProductieActori (Entrym, IdActor, IdProductie)
VALUES ('2010-05-01', 1, 1), -- Leonardo DiCaprio in Inception Production
       ('1993-03-01', 3, 2), -- Jeff Goldblum in Jurassic Park Production
       ('1994-08-01', 2, 3),-- Samuel L. Jackson in Pulp Fiction Production
       ('1994-09-01', 4, 3); -- Uma Thurman in Pulp Fiction Production
	   
INSERT INTO ProductieActori (Entrym, IdActor, IdProductie)
values	   ('1994-08-01', 2, 1),
	   ('1994-08-01', 2, 2);

---primeste un actor,un moment si o productie si le adauga
CREATE or ALTER PROCEDURE AdaugaProductieActori
(
	@actorId INT,
	@prodId INT,
	@moment datetime
)
AS 
BEGIN
	IF EXISTS(
		SELECT 1 
        FROM ProductieActori
        WHERE IdProductie = @prodId AND IdActor= @actorId
		)
	 BEGIN
        
        UPDATE ProductieActori
        SET Entrym=@moment
        WHERE IdProductie = @prodId AND IdActor= @actorId;
    END
    ELSE
    BEGIN
        
        INSERT INTO ProductieActori(Entrym, IdActor, IdProductie)
        VALUES (@moment, @actorId, @prodId);
    END
END


---un view care arata numele actorilor care apar in toate productiile

CREATE OR ALTER VIEW ActoriA AS
SELECT 
    a.Nume AS ActorName,
	COUNT(DISTINCT pa.IdProductie) AS Countf
FROM Actori a
JOIN ProductieActori pa ON a.Id = pa.IdActor
JOIN Productie p on p.Id=pa.IdProductie
GROUP BY a.Id,a.Nume
HAVING COUNT(DISTINCT pa.IdProductie) =(SELECT COUNT(*) FROM Productie);


select * from ActoriA
CREATE OR ALTER FUNCTION FilmeCuT(@T INT)
RETURNS TABLE
AS
RETURN
(
    SELECT 
        
        f.Nume AS FilmName,
		f.Datar,
        COUNT(p.IdFilm) AS Countf
    FROM Filme f
    JOIN Productie p ON f.Id = p.IdFilm
	WHERE 
		f.Datar>'2018-01-01'
    GROUP BY  f.Nume,f.Datar
    HAVING COUNT(p.IdFilm) >= @T
);

select * from FilmeCuT(1)
