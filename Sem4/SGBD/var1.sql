Create database CofetariiBriose
go
use CofetariiBriose
go


CREATE TABLE Cofetarie
(Id INT PRIMARY KEY IDENTITY,
Denumire varchar(50),
)


CREATE TABLE Briosa
(Id INT PRIMARY KEY IDENTITY,
Denumire varchar(50),
Id_cofetarie INT FOREIGN KEY REFERENCES Cofetarie(Id)
)

INSERT INTO Cofetarie values ('cofetarie1'), ('cofetarie2'), ('cofetarie3')

INSERT INTO Briosa values ('b1',1),('b2',1),('b3',2)

CREATE NONCLUSTERED INDEX IDX_Briosa_IdCofetarie2
ON Briosa (Id_cofetarie,Denumire);

SELECT * FROM Briosa WHERE Id_cofetarie = 1;
SELECT B.Denumire, C.Denumire AS Cofetarie
FROM Briosa B
JOIN Cofetarie C ON B.Id_cofetarie = C.Id
WHERE B.Id_cofetarie = 1
ORDER BY B.Denumire;