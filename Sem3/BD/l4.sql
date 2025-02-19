Create database AdministrareLibrarie
go
use AdministrareLibrarie
go


-- Crearea tabelelor
CREATE TABLE Domenii (
    ID_Domeniu INT PRIMARY KEY IDENTITY(1,1),
    Nume NVARCHAR(100) NOT NULL,
    Descriere NVARCHAR(255)
);

CREATE TABLE Autori (
    ID_Autor INT PRIMARY KEY IDENTITY(1,1),
    Nume NVARCHAR(100) NOT NULL
);

CREATE TABLE Carti (
    ID_Carte INT PRIMARY KEY IDENTITY(1,1),
    Titlu NVARCHAR(200) NOT NULL,
    ID_Domeniu INT NOT NULL,
    FOREIGN KEY (ID_Domeniu) REFERENCES Domenii(ID_Domeniu)
);

CREATE TABLE Librarii (
    ID_Librarie INT PRIMARY KEY IDENTITY(1,1),
    Nume NVARCHAR(100) NOT NULL,
    Adresa NVARCHAR(200) NOT NULL
);

CREATE TABLE CartiLibrarii (
    ID_Carte INT NOT NULL,
    ID_Librarie INT NOT NULL,
    DataAchizitie DATE NOT NULL,
    PRIMARY KEY (ID_Carte, ID_Librarie),
    FOREIGN KEY (ID_Carte) REFERENCES Carti(ID_Carte),
    FOREIGN KEY (ID_Librarie) REFERENCES Librarii(ID_Librarie)
);

CREATE TABLE AutoriCarti (
    ID_Autor INT NOT NULL,
    ID_Carte INT NOT NULL,
    PRIMARY KEY (ID_Autor, ID_Carte),
    FOREIGN KEY (ID_Autor) REFERENCES Autori(ID_Autor),
    FOREIGN KEY (ID_Carte) REFERENCES Carti(ID_Carte)
);


---Procedură stocată pentru a asocia un autor cu o carte
CREATE PROCEDURE AdaugaAutorLaCarte
    @NumeAutor NVARCHAR(100),
    @TitluCarte NVARCHAR(200)
AS
BEGIN
    -- Verifică dacă autorul există deja
    DECLARE @ID_Autor INT;
    SELECT @ID_Autor = ID_Autor
    FROM Autori
    WHERE Nume = @NumeAutor;

    -- Dacă autorul nu există, îl adăugăm
    IF @ID_Autor IS NULL
    BEGIN
        INSERT INTO Autori (Nume) VALUES (@NumeAutor);
        SET @ID_Autor = SCOPE_IDENTITY();
    END

    -- Verifică dacă cartea există
    DECLARE @ID_Carte INT;
    SELECT @ID_Carte = ID_Carte
    FROM Carti
    WHERE Titlu = @TitluCarte;

    -- Dacă cartea nu există, aruncăm o eroare
    IF @ID_Carte IS NULL
    BEGIN
        PRINT 'Eroare: Cartea nu există.';
        RETURN;
    END

    -- Asociază autorul la carte
    IF NOT EXISTS (
        SELECT 1 FROM AutoriCarti WHERE ID_Autor = @ID_Autor AND ID_Carte = @ID_Carte
    )
    BEGIN
        INSERT INTO AutoriCarti (ID_Autor, ID_Carte) VALUES (@ID_Autor, @ID_Carte);
    END
    ELSE
    BEGIN
        PRINT 'Autorul este deja asociat la această carte.';
    END
END;


---view pt numarul cartilor cumparate dupa 2010 pt fiecare librarie

CREATE VIEW NumarCartiDupa2010 AS
SELECT 
    L.Nume AS NumeLibrarie,
    COUNT(CL.ID_Carte) AS NrCarti
FROM 
    Librarii L
    INNER JOIN CartiLibrarii CL ON L.ID_Librarie = CL.ID_Librarie
WHERE 
    YEAR(CL.DataAchizitie) > 2010
GROUP BY 
    L.Nume
HAVING 
    COUNT(CL.ID_Carte) >= 5
ORDER BY 
    L.Nume ASC;


---functie pentru lista cartilor scrise de un numar dat de autori
CREATE FUNCTION ListaCartiDupaNrAutori (@NrAutori INT)
RETURNS TABLE
AS
RETURN
(
    SELECT 
        L.Nume AS Librarie,
        L.Adresa,
        C.Titlu,
        COUNT(AC.ID_Autor) AS NrAutori
    FROM 
        Librarii L
        INNER JOIN CartiLibrarii CL ON L.ID_Librarie = CL.ID_Librarie
        INNER JOIN Carti C ON CL.ID_Carte = C.ID_Carte
        INNER JOIN AutoriCarti AC ON C.ID_Carte = AC.ID_Carte
    GROUP BY 
        L.Nume, L.Adresa, C.Titlu
    HAVING 
        COUNT(AC.ID_Autor) = @NrAutori
);
