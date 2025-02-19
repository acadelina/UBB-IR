Create database AdministrareShoes
go
use AdministrareShoes
go


CREATE TABLE Shops
(Id INT PRIMARY KEY IDENTITY,
Nume varchar(50),
Oras varchar(50)
)


CREATE TABLE Femei
(Id INT PRIMARY KEY IDENTITY,
Nume varchar(50),
maxim int
)


CREATE TABLE Modele
(Id INT PRIMARY KEY IDENTITY,
Nume varchar(50),
Sezon varchar(50)
 )


CREATE TABLE Shoes
(Id INT PRIMARY KEY IDENTITY,

Pret int,
IdModel INT FOREIGN KEY REFERENCES Modele(Id),
)

CREATE TABLE Stocuri
(
	Id INT PRIMARY KEY IDENTITY,
	IdShoe INT FOREIGN KEY REFERENCES Shoes(Id),
	IdShop INT FOREIGN KEY REFERENCES Shops(Id),
	stoc int
	)


CREATE TABLE Tranzactii
(Id INT PRIMARY KEY IDENTITY,
IdFemeie INT FOREIGN KEY REFERENCES Femei(Id),
IdShoe INT FOREIGN KEY REFERENCES Shoes(Id),
Suma int,
Numar int
)

INSERT INTO Shops (Nume, Oras) 
VALUES 
('ShopOne', 'Bucuresti'),
('ShopTwo', 'Cluj'),
('ShopThree', 'Timisoara');

-- Populare tabel Femei
INSERT INTO Femei (Nume, maxim) 
VALUES 
('Maria', 500),
('Elena', 700),
('Ioana', 400);

-- Populare tabel Modele
INSERT INTO Modele (Nume, Sezon) 
VALUES 
('Model1', 'Primavara'),
('Model2', 'Vara'),
('Model3', 'Toamna');

-- Populare tabel Shoes
INSERT INTO Shoes (Pret, IdModel) 
VALUES 
(300, 1), 
(450, 2),
(250, 3),
(500, 1);

-- Populare tabel Stocuri
INSERT INTO Stocuri (IdShoe, IdShop, stoc) 
VALUES 
(1, 1, 10),
(2, 1, 5),
(3, 2, 8),
(4, 3, 7),
(1, 2, 4),
(3, 3, 2);

-- Populare tabel Tranzactii
INSERT INTO Tranzactii (IdFemeie, IdShoe, Suma, Numar) 
VALUES 
(1, 1, 300, 1),
(2, 2, 900, 2),
(3, 3, 250, 1),
(1, 4, 500, 1),
(2, 3, 750, 3);
---Primeste un papuc,un magazin si numarul de papuci si adauga papucul in magazin


CREATE or ALTER PROCEDURE StergeTranzactii
(
	@shopId INT,
	@shoeId INT,
	@nr int
)
AS 
BEGIN
	IF EXISTS(
		SELECT 1 
        FROM Stocuri
        WHERE IdShoe = @shoeId AND IdShop= @shopId
		)
	 BEGIN
        
        UPDATE Stocuri
        SET stoc = stoc + @nr
        WHERE IdShoe = @shoeId AND IdShop = @shopId;
    END
    ELSE
    BEGIN
        
        INSERT INTO Stocuri (IdShoe, IdShop, stoc)
        VALUES (@shoeId, @shopId, @nr);
    END
END

exec StergeTranzactii @shopId=3,@shoeId=1,@nr=30;
select * From Stocuri 
---Creați un view care arată femeile care au cumpărat cel puțin 2 perechi de pantofi dintr-un anumit model.
CREATE OR ALTER VIEW WomenWithAtLeastTwoShoesPerModel AS
SELECT 
    w.Nume AS WomanName,
    sm.Nume AS ShoeModelName,
    SUM(p.Numar) AS TotalShoesBought
FROM Tranzactii p
JOIN Femei w ON p.IdFemeie = w.Id
JOIN Shoes s ON p.IdShoe = s.Id
JOIN Modele sm ON s.IdModel = sm.Id
GROUP BY w.Nume, sm.Nume
HAVING SUM(p.Numar) >= 2;

select * from WomenWithAtLeastTwoShoesPerModel;

---Creați o funcție care listează pantofii care se găsesc în cel puțin T magazine de prezentare, unde T este un parametru al funcției.

CREATE OR ALTER FUNCTION ShoesInAtLeastTShops(@T INT)
RETURNS TABLE
AS
RETURN
(
    SELECT 
        s.Id AS ShoeId,
        sm.Nume AS ShoeModelName,
        COUNT(ss.IdShoe) AS ShopCount
    FROM Shoes s
    JOIN Stocuri ss ON s.Id = ss.IdShoe
    JOIN Modele sm ON s.IdModel = sm.Id
    GROUP BY s.Id, sm.Nume
    HAVING COUNT(ss.IdShop) >= @T
);

select * from ShoesInAtLeastTShops(2)