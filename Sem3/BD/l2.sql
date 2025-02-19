Create database AdministrareBanca
go
use AdministrareBanca
go


CREATE TABLE Clienti
(Id INT PRIMARY KEY IDENTITY,
Nume varchar(50),
Datan datetime
)


CREATE TABLE ATM
(Id INT PRIMARY KEY IDENTITY,
Adresa varchar(50)
)


CREATE TABLE Conturi
(Id INT PRIMARY KEY IDENTITY,
Iban varchar(50),
Balance int,
IdProprietar INT FOREIGN KEY REFERENCES Clienti(Id) )


CREATE TABLE Carduri
(Id INT PRIMARY KEY IDENTITY,
Numar varchar(50),
Cvv int,
IdCont INT FOREIGN KEY REFERENCES Conturi(Id),
)


CREATE TABLE Tranzactii
(Id INT PRIMARY KEY IDENTITY,
IdCard INT FOREIGN KEY REFERENCES Carduri(Id),
IdATM INT FOREIGN KEY REFERENCES ATM(Id),
Suma int,
Time datetime NOT NULL
)



---STERGEM TOATE TRANZACTIILE CARE AU LEGATURA CU CARDUL DAT( ID)

CREATE or ALTER PROCEDURE StergeTranzactii
(
	@cardId INT
)
AS 
BEGIN
	DELETE FROM Tranzactii
	WHERE IdCard=@cardId
END


---STERGEM TOATE TRANZACTIILE CARE AU LEGATURA CU CARDUL DAT(numar)

CREATE or ALTER PROCEDURE StergeTranzactii2
(
	@numarCard varchar(50)
)
AS 
BEGIN
	DECLARE @cardId INT;

    
    SELECT @cardId = Id
    FROM Carduri
    WHERE Numar = @numarCard;

    
    IF @cardId IS NULL
    BEGIN
        PRINT 'Cardul cu acest numar nu exista.';
        RETURN;
    END

    
    DELETE FROM Tranzactii
    WHERE IdCard = @cardId;
END


---UN VIEW CARE AFISEAZA NUMERELE CARDURILOR CARE AU FOST FOLOSITE IN TRANZACTII LA TOATE ATM URILE

CREATE OR ALTER VIEW e3 AS
	SELECT DISTINCT c.Numar 
	FROM Carduri c
	JOIN Tranzactii t ON c.Id=t.Id
	GROUP BY c.Numar
	HAVING COUNT(DISTINCT t.IdATM)=(SELECT COUNT(*) FROM ATM)


---O FUNCTIE CARE AFISEAZA CARDURILE(NUMAR+cvv) CARE AU TOTALUL TRANZACTIILOR MAI MARE DE 2000

CREATE OR ALTER FUNCTION e4()
	returns table
AS
RETURN
	SELECT c.Numar,c.Cvv as CARD
	FROM Carduri c 
	JOIN Tranzactii t ON t.IdCard=c.Id
	GROUP BY c.Numar, c.Cvv
	HAVING SUM(t.Suma)>2000
	