Create database Premii
go
use Premii
go


CREATE TABLE Tip
(Id_tip INT PRIMARY KEY IDENTITY,
Nume varchar(50),
Anual int,
Statusp varchar(50),
Nr_castigatori int
)


CREATE TABLE Premiu
(Id_premiu INT PRIMARY KEY IDENTITY,
Nume varchar(50),
Sponsor varchar(50),
An int,
Nume_castigator varchar(50),
Varsta int,
Id_tip INT FOREIGN KEY REFERENCES Tip(Id_tip)
)

INSERT INTO Tip values ('tip1',1,'activ',10), ('tip2',0,'inactiv',5), ('tip3',1,'activ',15)

INSERT INTO Premiu values ('p1','s1',2023,'castigator',20,1), ('p2','s2',2023,'castigator2',22,1), ('p3','s3',2024,'castigator3',20,2), ('p4','s4',2023,'castigator4',20,3)

INSERT INTO Premiu values ('p1','s1',2023,'castigator',17,1)

---tipurile de premii care au minim 3 castigatori

select Tip.Id_tip,Tip.Nume,Tip.Anual,Tip.Statusp,Tip.Nr_castigatori from Tip
join Premiu on Tip.Id_tip=Premiu.Id_tip
group by Tip.Id_tip,Tip.Nume,Tip.Anual,Tip.Statusp,Tip.Nr_castigatori
having count(*)>=3

---varsta medie a castigatorilor sub varsta de 18 ani
select avg(Varsta) as VarstaMedieSub18 from Premiu
where Varsta<18

select * from Premiu

---index pe varsta
CREATE NONCLUSTERED INDEX IDX_Varsta
ON Premiu (Varsta);
