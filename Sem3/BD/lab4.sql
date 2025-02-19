INSERT INTO Tables(Name) VALUES
('Clienti'),('Comenzi'),('Comenzi_Produse');
GO

CREATE OR ALTER VIEW VClienti
AS
SELECT Cnp,Nume,Varsta
FROM Clienti
GO


CREATE OR ALTER VIEW VComenzi
AS 
SELECT Cm.Id_comanda, Cl.Nume
FROM Comenzi Cm
INNER JOIN Clienti Cl ON Cm.Client=Cl.Cnp
GO

CREATE OR ALTER VIEW VComezi_Produse
AS 
SELECT Cl.Nume,P.Denumire,CP.Pret
FROM Comenzi_Produse CP
INNER JOIN Produse P ON P.Id_produs=CP.Pid
INNER JOIN Clienti Cl ON Cl.Cnp=CP.Cid
GO

INSERT INTO Views VALUES
('VClienti'),('VComenzi'),('VComenzi_Produse')

INSERT INTO Tests(Name) VALUES
('Inserare10'),
('Inserare100'),
('Inserare1000'),
('Sterge10'),
('Sterge100'),
('Sterge1000'),
('Evaluare')
GO

INSERT INTO TestTables VALUES
(1, 1, 10, 1),
(2, 1, 100, 1),
(3, 1, 1000, 1),
(1, 2, 10, 2),
(2, 2, 100, 2),
(3, 2 ,1000, 2),
(1, 3, 10, 3),
(2, 3, 100, 3),
(3, 3, 1000, 3),

(4, 1, 10, 3),
(5, 1, 100, 3),
(6, 1, 1000, 3),
(4, 2, 10, 2),
(5, 2, 100, 2),
(6, 2 ,1000, 2),
(4, 3, 10, 1),
(5, 3, 100, 1),
(6, 3, 1000, 1)
GO


INSERT INTO TestViews VALUES 
(7,1),
(7,2),
(7,3)
GO

--- INSERARE IN TABELA CLIENTI ---
CREATE or ALTER PROCEDURE InsertClienti (@rows int)
AS
BEGIN
	DECLARE @cnp int
	DECLARE @nume VARCHAR(50)
	DECLARE @varsta int
	DECLARE @i int
	DECLARE @lastCnp int
	SET @nume='NumeClient'
	SET @cnp=2000
	SET @i=1

	WHILE @i<=@rows
	BEGIN
		SET @cnp=2000+@i
		SELECT TOP 1 @lastCnp = Clienti.Cnp FROM dbo.Clienti ORDER BY Clienti.Cnp DESC
		IF @lastCnp>2000
			SET @cnp=@lastCnp+1
		INSERT INTO Clienti VALUES (@cnp,@nume,null)
		SET @i=@i+1
	END
END
GO

---STERGERE DIN TABELA CLIENTI---
CREATE OR ALTER PROCEDURE DeleteClienti (@rows int)
AS
BEGIN
	DECLARE @cnp int
	DECLARE @i int
	DECLARE @lastCnp int

	SET @cnp=2000
	SET @i=@rows

	WHILE @i>0
	BEGIN
		SET @cnp=2000+@i
		SELECT TOP 1 @lastCnp= Clienti.Cnp FROM dbo.Clienti ORDER BY Clienti.Cnp DESC
		IF @lastCnp>@cnp
			SET @cnp=@lastCnp
		DELETE FROM Clienti WHERE Clienti.Cnp=@cnp
		SET @i=@i-1
	END
END
GO



--- INSERARE IN TABELA Produse ---
CREATE or ALTER PROCEDURE InsertProduse (@rows int)
AS
BEGIN
	DECLARE @id int
	DECLARE @nume VARCHAR(50)
	DECLARE @i int
	DECLARE @lastId int
	SET @nume='NumeProdus'
	SET @id=2000
	SET @i=1

	WHILE @i<=@rows
	BEGIN
		SET @id=2000+@i
		SELECT TOP 1 @lastId = Produse.Id_produs FROM dbo.Produse ORDER BY Produse.Id_produs DESC
		IF @lastId>2000
			SET @id=@lastId+1
		INSERT INTO Produse VALUES (@id,@nume,0,0,1)
		SET @i=@i+1
	END
END
GO


---INSERARE IN TABELA COMENZI---

CREATE or ALTER PROCEDURE InsertComenzi (@rows int)
AS
BEGIN
	DECLARE @id int
	DECLARE @data date
	DECLARE @pret int
	DECLARE @i int
	DECLARE @lastId int
	SET @data='1998-04-11'
	SET @id=2000
	SET @i=1
	SET @pret=100
	
	exec InsertClienti @rows
	WHILE @i<=@rows
	BEGIN
		SET @id=2000+@i
		SELECT TOP 1 @lastId = Comenzi.Id_comanda FROM dbo.Comenzi ORDER BY Comenzi.Id_comanda DESC
		IF @lastId>2000
			SET @id=@lastId+1
		INSERT INTO Comenzi VALUES (@id,@data,@pret,@id)
		SET @i=@i+1
	END
END
GO

---STERGERE DIN TABELA COMENZI---
CREATE OR ALTER PROCEDURE DeleteComenzi (@rows int)
AS
BEGIN
	DECLARE @id int
	DECLARE @i int
	DECLARE @lastId int

	SET @id=2000
	SET @i=@rows
	
	WHILE @i>0
	BEGIN
		SET @id=2000+@i
		SELECT TOP 1 @lastId= Comenzi.Id_comanda FROM dbo.Comenzi ORDER BY Comenzi.Id_comanda DESC
		IF @lastId>@id
			SET @id=@lastId
		DELETE FROM Comenzi WHERE Comenzi.Id_comanda=@id 
		SET @i=@i-1
	END
END
GO

---INSERARE IN TABELA COMENZI_PRODUSE---
CREATE OR ALTER PROCEDURE InsertComenzi_Produse(@rows int)
AS
BEGIN
	DECLARE @i int
	SET @i=@rows
	
	exec InsertProduse @rows
	exec InsertComenzi @rows
	
	DECLARE @idC int, @pret int;
	DECLARE cursorComenziProduse CURSOR SCROLL FOR
	SELECT Id_comanda,Pret_total FROM Comenzi;

	OPEN cursorComenziProduse;
	FETCH LAST FROM cursorComenziProduse INTO @idC,@pret;
	WHILE @@FETCH_STATUS=0 AND @i>0
	BEGIN
		INSERT INTO Comenzi_Produse(Cid,Pid,Cantitate,Pret)
		VALUES (@idC,2001,0,@pret)

		FETCH PRIOR FROM cursorComenziProduse INTO @idC,@pret;
		SET @i=@i-1
	END
	
	
	CLOSE cursorComenziProduse;
	DEALLOCATE cursorComenziProduse;
END
GO

CREATE OR ALTER PROCEDURE DeleteComenziProduse(@rows INT)
AS
BEGIN
    DECLARE @i INT;
    DECLARE @idComanda INT;
    DECLARE @idProdus INT;

    SET @i = @rows;

    
    WHILE @i > 0
    BEGIN
        
        SELECT TOP 1 @idComanda = Comenzi.Id_comanda
        FROM dbo.Comenzi
        ORDER BY Comenzi.Id_comanda DESC;

        
        IF @idComanda IS NOT NULL
        BEGIN
            
            DELETE FROM Comenzi_Produse WHERE Cid = @idComanda;

            
            DELETE FROM Comenzi WHERE Id_comanda = @idComanda;

        END

        
        SET @i = @i - 1;
    END
END
GO


CREATE OR ALTER PROCEDURE Inserare10 (@Tabela VARCHAR(20))
AS
BEGIN
	IF @Tabela='Comenzi'
	exec InsertComenzi 10
	IF @Tabela='Clienti'
	exec InsertClienti 10
	IF @Tabela='Comenzi_produse'
	exec InsertComenzi_Produse 10
	else PRINT 'Nume invalid'
END
GO


CREATE OR ALTER PROCEDURE Inserare100 (@Tabela VARCHAR(20))
AS
BEGIN
	IF @Tabela='Comenzi'
	exec InsertComenzi 100
	IF @Tabela='Clienti'
	exec InsertClienti 100
	IF @Tabela='Comenzi_produse'
	exec InsertComenzi_Produse 100
	else PRINT 'Nume invalid'
END
GO


CREATE OR ALTER PROCEDURE Inserare1000 (@Tabela VARCHAR(20))
AS
BEGIN
	IF @Tabela='Comenzi'
	exec InsertComenzi 1000
	IF @Tabela='Clienti'
	exec InsertClienti 1000
	IF @Tabela='Comenzi_produse'
	exec InsertComenzi_Produse 1000
	else PRINT 'Nume invalid'
END
GO


CREATE OR ALTER PROCEDURE Inserare10000 (@Tabela VARCHAR(20))
AS
BEGIN
	IF @Tabela='Comenzi'
	exec InsertComenzi 10000
	IF @Tabela='Clienti'
	exec InsertClienti 10000
	IF @Tabela='Comenzi_produse'
	exec InsertComenzi_Produse 10000
	else PRINT 'Nume invalid'
END
GO


CREATE OR ALTER PROCEDURE Stergere10 (@Tabela VARCHAR(20))
AS
BEGIN
	IF @Tabela='Comenzi'
	exec DeleteComenzi 10
	IF @Tabela='Clienti'
	exec DeleteClienti 10
	IF @Tabela='Comenzi_produse'
	exec DeleteComenziProduse 10
	else PRINT 'Nume invalid'
END
GO


CREATE OR ALTER PROCEDURE Stergere100 (@Tabela VARCHAR(20))
AS
BEGIN
	IF @Tabela='Comenzi'
	exec DeleteComenzi 100
	IF @Tabela='Clienti'
	exec DeleteClienti 100
	IF @Tabela='Comenzi_produse'
	exec DeleteComenziProduse 100
	else PRINT 'Nume invalid'
END
GO


CREATE OR ALTER PROCEDURE Stergere1000 (@Tabela VARCHAR(20))
AS
BEGIN
	IF @Tabela='Comenzi'
	exec DeleteComenzi 1000
	IF @Tabela='Clienti'
	exec DeleteClienti 1000
	IF @Tabela='Comenzi_produse'
	exec DeleteComenziProduse 1000
	else PRINT 'Nume invalid'
END
GO


CREATE OR ALTER PROCEDURE Stergere10000 (@Tabela VARCHAR(20))
AS
BEGIN
	IF @Tabela='Comenzi'
	exec DeleteComenzi 10000
	IF @Tabela='Clienti'
	exec DeleteClienti 10000
	IF @Tabela='Comenzi_produse'
	exec DeleteComenziProduse 10000
	else PRINT 'Nume invalid'
END
GO


CREATE OR ALTER PROCEDURE Evaluare (@View VARCHAR(20))
AS
BEGIN
	IF @View='Clienti'
	select * from VClienti
	IF @View='Comenzi'
	select * from VComenzi
	IF @View='Comenzi_Produse'
	select * from VComezi_Produse
	else PRINT 'Nume invalid'
END
GO

--- Procedura principala ----------------------------------------------
CREATE OR ALTER PROCEDURE Main (@Tabela VARCHAR(20))
AS
BEGIN
	DECLARE @t1 datetime, @t2 datetime, @t3 datetime
	DECLARE @desc NVARCHAR(2000)

	DECLARE @testInserare VARCHAR(20)
	DECLARE @testSterge VARCHAR(20)
	DECLARE @nrRows int
	DECLARE @idTest int

	SET @nrRows=10000
	SET @testInserare='Inserare' + CONVERT(VARCHAR (5),@nrRows)
	SET @testSterge='Stergere'++ CONVERT(VARCHAR (5),@nrRows)


	if @Tabela='Clienti'
		BEGIN
			SET @t1 =GETDATE()
			exec @testInserare Clienti
			exec @testSterge Clienti
			SET @t2 =GETDATE()
			exec Evaluare Clienti
			SET @t3 =GETDATE()
			SET @desc=N'Testul s-a facut '+@testInserare+', '+@testSterge+', EvaluareView pe tabela '+@Tabela
			INSERT INTO TestRuns VALUES (@desc,@t1,@t3)
			SELECT TOP 1 @idTest=T.TestRunID FROM dbo.TestRuns T ORDER BY T.TestRunID DESC
			INSERT INTO TestRunTables VALUES (@idTest,1,@t1,@t2)
			INSERT INTO TestRunViews VALUES (@idTest,1,@t2,@t3)
		END
	if @Tabela='Comenzi'
		BEGIN
			SET @t1 =GETDATE()
			exec @testInserare Comenzi
			exec @testSterge Comenzi
			SET @t2 =GETDATE()
			exec Evaluare Comenzi
			SET @t3 =GETDATE()
			SET @desc=N'Testul s-a facut '+@testInserare+', '+@testSterge+', EvaluareView pe tabela '+@Tabela
			INSERT INTO TestRuns VALUES (@desc,@t1,@t3)
			SELECT TOP 1 @idTest=T.TestRunID FROM dbo.TestRuns T ORDER BY T.TestRunID DESC
			INSERT INTO TestRunTables VALUES (@idTest,3,@t1,@t2)
			INSERT INTO TestRunViews VALUES (@idTest,3,@t2,@t3)
		END
	if @Tabela='Comenzi_Produse'
		BEGIN
			SET @t1 =GETDATE()
			exec @testInserare Comenzi_produse
			exec @testSterge Comenzi_produse
			SET @t2 =GETDATE()
			exec Evaluare Comenzi_produse
			SET @t3 =GETDATE()
			SET @desc=N'Testul s-a facut '+@testInserare+', '+@testSterge+', EvaluareView pe tabela '+@Tabela
			INSERT INTO TestRuns VALUES (@desc,@t1,@t3)
			SELECT TOP 1 @idTest=T.TestRunID FROM dbo.TestRuns T ORDER BY T.TestRunID DESC
			INSERT INTO TestRunTables VALUES (@idTest,2,@t1,@t2)
			INSERT INTO TestRunViews VALUES (@idTest,2,@t2,@t3)
		END
	ELSE PRINT 'Tabela invalida'
END


exec Main Clienti
exec Main Comenzi
exec Main Comenzi_Produse

select * from TestRuns
select * from TestRunTables
select * from TestRunViews
DELETE FROM TestRuns
DELETE FROM TestRunTables
DELETE FROM TestRunViews


DROP TABLE TestRunViews
DROP TABLE TestRunTables
DROP TABLE TestRuns
DROP TABLE TestTables
DROP TABLE TestViews
DROP TABLE Tests
DROP TABLE Tables
DROP TABLE Views