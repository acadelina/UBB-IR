Create database ArtistiMelodii
go
use ArtistiMelodii
go


CREATE TABLE Artist
(Id_artist INT PRIMARY KEY IDENTITY,
Nume varchar(50),
Varsta int
)


CREATE TABLE Melodie
(Id_melodie INT PRIMARY KEY IDENTITY,
Denumire varchar(50),
Id_artist INT FOREIGN KEY REFERENCES Artist(Id_artist)
)

INSERT INTO Artist values ('art1',30), ('art2',31), ('art3',20)

INSERT INTO Melodie values ('b1',1),('b2',1),('b3',2)

CREATE NONCLUSTERED INDEX IDX_Melodie_IdArtist
ON Melodie (Id_artist,Denumire);

SELECT * FROM Melodie WHERE Id_artist = 1;
SELECT B.Denumire, C.Denumire AS Cofetarie
FROM Briosa B
JOIN Cofetarie C ON B.Id_cofetarie = C.Id
WHERE B.Id_cofetarie = 1
ORDER BY B.Denumire;