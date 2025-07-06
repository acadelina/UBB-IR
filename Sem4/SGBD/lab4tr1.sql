

UPDATE Materiale SET
	Denumire='BBB' WHERE Id_material>100

delete from Materiale where Id_material>151

---DIRTY READS

BEGIN TRANSACTION
	INSERT INTO LogEvenimente(Eveniment, Detalii) 
    VALUES ('Dirty Read', 'TRANSACTION STARTED - Updating Materiale');
	UPDATE Materiale SET
	Denumire='AAA' WHERE Id_material>100
	INSERT INTO LogEvenimente(Eveniment, Detalii) 
    VALUES ('Dirty Read', 'UPDATE executed, sleeping 7 seconds');
	WAITFOR DELAY '00:00:7'
ROLLBACK TRANSACTION
INSERT INTO LogEvenimente(Eveniment, Detalii) 
VALUES ('Dirty Read', 'TRANSACTION ROLLED BACK');

---NON-REPEATABLE READS
INSERT INTO Materiale(Denumire) VALUES
('DENUMIRE')
BEGIN TRAN
INSERT INTO LogEvenimente(Eveniment, Detalii)  VALUES ('Non-Repeatable Read', 'TRANSACTION STARTED - waiting 10 seconds');
WAITFOR DELAY '00:00:10'
UPDATE Materiale SET Denumire='UPDATED' WHERE Denumire = 'DENUMIRE'
INSERT INTO LogEvenimente(Eveniment, Detalii) VALUES ('Non-Repeatable Read', 'UPDATED row to Denumire = UPDATED');
COMMIT TRAN
INSERT INTO LogEvenimente(Eveniment, Detalii) VALUES ('Non-Repeatable Read', 'TRANSACTION COMMITTED');

---PHANTOM READS
BEGIN TRAN
INSERT INTO LogEvenimente(Eveniment, Detalii) 
    VALUES ('Phantom Read', 'TRANSACTION STARTED - waiting 10 seconds before insert');
WAITFOR DELAY '00:00:10'
INSERT INTO Materiale(Denumire) VALUES ('PHANTOM')
INSERT INTO LogEvenimente(Eveniment, Detalii) 
    VALUES ('Phantom Read', 'Inserted row with Denumire = PHANTOM');
COMMIT TRAN
INSERT INTO LogEvenimente(Eveniment, Detalii) VALUES ('Phantom Read', 'TRANSACTION COMMITTED');


INSERT INTO Materiale(Denumire) VALUES ('Deadlock')
INSERT INTO Filtre_produse(Id_produs) VALUES (18)
update Materiale set Denumire='Deadlock' where Id_material=157
update Filtre_produse set Id_produs=18 where Id_filtru=156
select * from Produse
select * from Filtre_produse
select * from Materiale

delete from Filtre_Dimensiuni where Id_filtru=2

---DEADLOCK

--SET DEADLOCK_PRIORITY HIGH
SET DEADLOCK_PRIORITY LOW

-- transaction 1
INSERT INTO LogEvenimente(Eveniment, Detalii) VALUES ('DeadLock1', 'Start');
begin tran
INSERT INTO LogEvenimente(Eveniment, Detalii) VALUES ('DeadLock1', 'Update Materiale');
update Materiale set Denumire='deadlock 1' where Id_material=157
-- this transaction has exclusively lock on table Books
waitfor delay '00:00:10'
INSERT INTO LogEvenimente(Eveniment, Detalii) VALUES ('DeadLock1', 'Update Filtre_produse');
update Filtre_produse set Id_produs=2 where Id_filtru=156
commit tran

select * from Filtre_produse
select * from Materiale

CREATE OR ALTER PROCEDURE DeadLock1 AS
BEGIN
	SET TRANSACTION ISOLATION LEVEL SERIALIZABLE
		
		begin tran
		INSERT INTO LogEvenimente(Eveniment, Detalii) 
		VALUES ('DeadLock1', 'Inceput tranzactie');
		update Materiale set Denumire='deadlock 1' where Id_material=157
		waitfor delay '00:00:10'
		update Filtre_produse set Id_produs=2 where Id_filtru=156
		commit tran
		INSERT INTO LogEvenimente(Eveniment, Detalii) 
		VALUES ('DeadLock1', 'commited');
		SELECT 'OK' AS MSG;  
	
END
GO

