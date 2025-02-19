
--procedura care schimba tipul unei coloane
CREATE PROCEDURE ChangeClienti_nume_to_nvarchar
AS
	ALTER TABLE Clienti
	ALTER COLUMN Nume nvarchar(100);
	PRINT 'S-a schimbat tipul coloanei la nvarchar'
GO

--procedura inversa
CREATE PROCEDURE ChangeClienti_nume_to_varchar
AS
	ALTER TABLE Clienti
	ALTER COLUMN Nume varchar(100);
	PRINT 'S-a schimbat tipul coloanei la varchar'
GO

EXEC ChangeClienti_nume_to_nvarchar;

EXEC ChangeClienti_nume_to_varchar;
GO

--procedura ce adauga o constrangere de val implicita pt un camp
CREATE PROCEDURE Add_Default_Value_Produse_stock
AS
	ALTER TABLE Produse
	ADD CONSTRAINT df_stock
	DEFAULT 1 for stock;
	PRINT 'S-a adaugat constrangerea'
GO

--procedura inversa
CREATE PROCEDURE Delete_Default_Value_Produse_stock
AS
	ALTER TABLE Produse
	DROP CONSTRAINT df_stock; /* sau ALTER COLUMN City DROP DEFAULT; */
	PRINT 'S-a sters constrangerea'
GO

EXEC Add_Default_Value_Produse_stock;
EXEC Delete_Default_Value_Produse_stock;
GO

CREATE PROCEDURE Create_Table_ComenziFinalizate AS
CREATE TABLE ComenziFinalizate(
Cid int NOT NULL PRIMARY KEY,
Finalizat int NOT NULL
)
PRINT 'S-a creat un nou tabel [ComenziFinalizate]'
GO


CREATE PROCEDURE Adauga_Camp_nou AS
ALTER TABLE ComenziFinalizate
ADD Data_comanda date
PRINT 'S-a adaugat un camp nou in tabela [ComenziFinalizate]'
GO


CREATE PROCEDURE Adauga_cheie_straina AS
ALTER TABLE ComenziFinalizate
ADD CONSTRAINT CFid FOREIGN KEY(Cid) REFERENCES Comenzi(Id_comanda)
PRINT 'S-a adaugat cheie straina'
GO

EXEC Create_Table_ComenziFinalizate;
EXEC Adauga_Camp_nou;
EXEC Adauga_cheie_straina;
GO

CREATE PROCEDURE undo_adauga_tabel AS
DROP TABLE ComenziFinalizate
PRINT 'S-a sters tabelul [ComenziFinalizate]'
GO


CREATE PROCEDURE undo_adauga_camp AS
ALTER TABLE ComenziFinalizate
DROP COLUMN Data_comanda
PRINT 'S-a eliminat coloana [Data_comanda]  din [ComenziFinalizate]'
GO


CREATE PROCEDURE undo_adauga_cheie_straina AS
ALTER TABLE ComenziFinalizate
DROP CONSTRAINT CFid
PRINT 'S-a eliminat cheia straina'
GO

EXEC undo_adauga_cheie_straina;
EXEC undo_adauga_camp;
EXEC undo_adauga_tabel;
GO

Create Table Lista_Proceduri_VersiuniDB(
	ID INT PRIMARY KEY,
	nume_procedura varchar(100)
);

INSERT INTO Lista_Proceduri_VersiuniDB
values
(0, 'ChangeClienti_nume_to_nvarchar'),
(1, 'Add_Default_Value_Produse_stock'),
(2, 'Create_Table_ComenziFinalizate'),
(3, 'Adauga_Camp_Nou'),
(4, 'Adauga_cheie_straina');

Create Table Lista_Opus_Proceduri_VersiuniDB(
	ID INT PRIMARY KEY,
	nume_procedura varchar(100)
);


INSERT INTO Lista_Opus_Proceduri_VersiuniDB
values
(1, 'ChangeClienti_nume_to_varchar'),
(2, 'Delete_Default_Value_Produse_stock'),
(3, 'undo_adauga_tabel'),
(4, 'undo_adauga_camp'),
(5, 'undo_adauga_cheie_straina');


SELECT * FROM Lista_Proceduri_VersiuniDB;

GO

DROP TABLE IF EXISTS VersiuneDB
CREATE TABLE VersiuneDB (
	versionNo int
);

INSERT INTO VersiuneDB VALUES(0)


SELECT * FROM VersiuneDB

GO

DROP PROCEDURE main;
GO


CREATE PROCEDURE main
@Versiune int
AS
BEGIN
	 IF @Versiune>5
	 BEGIN
		 RAISERROR('nu exista decat 6 versiuni ale DB-ul (de la 0 la 5 inclusiv)', 16, 1);
		RETURN;
	 END

	 DECLARE @Versiune_actuala AS INT
	 SELECT @Versiune_actuala = versionNo
	 FROM VersiuneDB;

	 PRINT 'versiunea actuala este :'; 
	 PRINT @Versiune_actuala;
	 PRINT 'Schimbam la veriunea :'; 
	 PRINT @Versiune;

	 IF @Versiune=@Versiune_actuala
	 BEGIN
		PRINT 'Suntem deja in aceasta versiune!';
		RETURN;
	 END

	 DECLARE @Functie AS varchar(100);


	 IF @Versiune>@Versiune_actuala
	 BEGIN
		WHILE @Versiune!=@Versiune_actuala
		BEGIN

			SELECT @Functie = nume_procedura
			FROM Lista_Proceduri_VersiuniDB
			where @Versiune_actuala=ID;

			EXECUTE @Functie;

			SET @Versiune_actuala=@Versiune_actuala+1;

		END

		UPDATE VersiuneDB
		SET versionNo = @Versiune;

		RETURN;
	 END
	 
	 -- altfel daca  @Versiune < @Versiune_actuala

	 WHILE @Versiune!=@Versiune_actuala
		BEGIN

			set @Versiune_actuala=@Versiune_actuala-1;

			SELECT @Functie = nume_procedura
			FROM Lista_Opus_Proceduri_VersiuniDB
			where @Versiune_actuala=ID;

			EXECUTE @Functie;
		END
	 
	 UPDATE VersiuneDB
	 SET versionNo = @Versiune;
	 RETURN;
END

go



exec main 0
exec main 1
exec main 2
exec main 3
exec main 4
exec main 10

