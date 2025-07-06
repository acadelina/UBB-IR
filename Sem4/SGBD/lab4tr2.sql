
---DIRTY READS 2

SET TRANSACTION ISOLATION LEVEL READ COMMITTED -- Problem: UNCOMMITTED ::Solution: COMMITED
	BEGIN TRAN
	INSERT INTO LogEvenimente(Eveniment, Detalii) VALUES ('Dirty Read', 'SELECT initial');
	SELECT * FROM Materiale
	WAITFOR DELAY '00:00:10'
	INSERT INTO LogEvenimente(Eveniment, Detalii) VALUES ('Dirty Read', 'SELECT dupa delay');
	SELECT * FROM Materiale
COMMIT TRAN
INSERT INTO LogEvenimente(Eveniment, Detalii) VALUES 
('Dirty Read', 'TRANZACTIE COMMIT');

select* from Materiale
select* from Filtre_produse

---NON-REPEATABLE READS  2

SET TRANSACTION ISOLATION LEVEL READ COMMITTED -- Problem: SET TRANSACTION ISOLATION LEVEL READ COMMITTED :: Solution: SET TRANSACTION ISOLATION LEVEL TO REPEATABLE READ
	BEGIN TRAN
	INSERT INTO LogEvenimente(Eveniment, Detalii) VALUES ('Non-Repeatable Read', 'Start: nivel READ COMMITTED');
	SELECT * FROM Materiale
	INSERT INTO LogEvenimente(Eveniment, Detalii) VALUES ('Non-Repeatable Read', 'SELECT initial');
	WAITFOR DELAY '00:00:15'
	SELECT * FROM Materiale
	INSERT INTO LogEvenimente(Eveniment, Detalii) VALUES ('Non-Repeatable Read', 'SELECT dupa delay');
COMMIT TRAN
INSERT INTO LogEvenimente(Eveniment, Detalii) VALUES ('Non-Repeatable Read', 'TRANZACTIE COMMITATA');


---PHANTOM READS 2
SET TRANSACTION ISOLATION LEVEL REPEATABLE READ  -- Problem:  SET TRANSACTION ISOLATION LEVEL TO REPEATABLE READ :: Solution:SET TRANSACTION ISOLATION LEVEL TO SERIALIZABLE
	BEGIN TRAN
	INSERT INTO LogEvenimente(Eveniment, Detalii) VALUES ('Phantom Read', 'Start: nivel SERIALIZABLE');
	SELECT * FROM Materiale
	INSERT INTO LogEvenimente(Eveniment, Detalii) VALUES ('Phantom Read', 'SELECT initial');
	WAITFOR DELAY '00:00:15'
	SELECT * FROM Materiale
	INSERT INTO LogEvenimente(Eveniment, Detalii) VALUES ('Phantom Read', 'SELECT dupa delay');
COMMIT TRAN
INSERT INTO LogEvenimente(Eveniment, Detalii) VALUES ('Phantom Read', 'TRANZACTIE COMMITATA');

---DEADLOCK


SET DEADLOCK_PRIORITY HIGH
--SET DEADLOCK_PRIORITY LOW

-- transaction 2
begin tran
INSERT INTO LogEvenimente(Eveniment, Detalii) VALUES ('DeadLock', 'Start');
update Filtre_produse set Id_produs=3 where Id_filtru=156
INSERT INTO LogEvenimente(Eveniment, Detalii) VALUES ('DeadLock2', 'Update Filtre_produse');
-- this transaction has exclusively lock on table Books
waitfor delay '00:00:10'
update Materiale set Denumire='deadlock 2' where Id_material=157
INSERT INTO LogEvenimente(Eveniment, Detalii) VALUES ('DeadLock2', 'Update Materiale');
commit tran

CREATE OR ALTER PROCEDURE DeadLock2 AS
BEGIN
	SET TRANSACTION ISOLATION LEVEL SERIALIZABLE
			
		begin tran
		INSERT INTO LogEvenimente(Eveniment, Detalii) 
		VALUES ('DeadLock2', 'Inceput tranzactie');
		update Filtre_produse set Id_produs=3 where Id_filtru=156
		waitfor delay '00:00:10'
		update Materiale set Denumire='deadlock 2' where Id_material=157
		commit tran
		INSERT INTO LogEvenimente(Eveniment, Detalii) 
		VALUES ('DeadLock2', 'commited');
		SELECT 'OK' AS MSG;  
END
GO

CREATE TABLE LogEvenimente (
    Id INT IDENTITY(1,1) PRIMARY KEY,
    Eveniment NVARCHAR(100),
    Detalii NVARCHAR(MAX),
    Timp DATETIME DEFAULT GETDATE()
);
