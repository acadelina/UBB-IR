Create database MagazinHaine
go
use MagazinHaine
go

CREATE TABLE Clienti
(Cnp INT PRIMARY KEY,
Nume varchar(50),
Varsta int)

CREATE TABLE Comenzi
(Id_comanda INT PRIMARY KEY IDENTITY,
DataComanda date,
Pret_total int,
Client INT FOREIGN KEY REFERENCES Clienti(Cnp)
)

CREATE TABLE Categorii
(Id_categorie INT PRIMARY KEY IDENTITY,
Titlu varchar(50),
Descriere varchar(100)
)

CREATE TABLE Produse
(Id_produs INT PRIMARY KEY IDENTITY,
Denumire varchar(50),
Stock int,
Pret int,
Categorie INT FOREIGN KEY REFERENCES Categorii(Id_categorie)
)

CREATE TABLE Comenzi_Produse
(Cid INT FOREIGN KEY REFERENCES Comenzi(Id_comanda),
Pid INT FOREIGN KEY REFERENCES Produse(Id_produs),
CONSTRAINT pk_ComenziProduse PRIMARY KEY (Cid,Pid),
Cantitate int,
Pret int
)

CREATE TABLE Dimensiuni
(Id_dimensiune INT PRIMARY KEY IDENTITY,
Denumire varchar(50)
)

CREATE TABLE Filtre_produse
(Id_filtru INT PRIMARY KEY IDENTITY,
Id_produs INT FOREIGN KEY REFERENCES Produse(Id_produs)
)

CREATE TABLE Filtre_Dimensiuni
(Id_filtru INT FOREIGN KEY REFERENCES Filtre_Produse(Id_filtru),
Id_dimensiune INT FOREIGN KEY REFERENCES Dimensiuni(Id_dimensiune),
CONSTRAINT pk_FiltreDimensiuni PRIMARY KEY(Id_filtru,Id_dimensiune)
)

CREATE TABLE Materiale
(Id_material INT PRIMARY KEY IDENTITY,
Denumire varchar(50)
)

CREATE TABLE Culori
(Id_culoare INT PRIMARY KEY IDENTITY,
Denumire varchar(50)
)

CREATE TABLE Filtre_Materiale
(Id_filtru INT FOREIGN KEY REFERENCES Filtre_Produse(Id_filtru),
Id_material INT FOREIGN KEY REFERENCES Materiale(Id_material),
CONSTRAINT pk_FiltreMateriale PRIMARY KEY(Id_filtru,Id_material)
)

CREATE TABLE Filtre_Culori
(Id_filtru INT FOREIGN KEY REFERENCES Filtre_Produse(Id_filtru),
Id_culoare INT FOREIGN KEY REFERENCES Culori(Id_culoare),
CONSTRAINT pk_FiltreCulori PRIMARY KEY(Id_filtru,Id_culoare)
)

INSERT INTO Clienti(Cnp, Nume, Varsta)
VALUES (1264560, 'Andreea', 20),(1264561, 'Adrian', 21)


INSERT INTO Clienti(Cnp, Nume, Varsta)
VALUES (1264562, 'Mihai', 40),(1264563, 'Florin', 31),(1264564, 'Ana', 25),(1264565, 'Florica', 50),(1264566, 'Mihaela', 18),(1264567, 'Elena', 21),(1264568, 'Fiona', 19)

INSERT INTO Comenzi(DataComanda,Pret_total,Client)
VALUES ('2024-05-24',150,1264560)


INSERT INTO Comenzi(DataComanda,Pret_total,Client)
VALUES ('2024-05-22',550,1264563),('2024-07-02',400,1264563),('2024-09-21',520,1264565),('2024-03-22',550,1264564),('2024-01-02',750,1264567),('2024-10-12',400,1264568),('2024-05-22',850,1264561),('2024-12-22',950,1264562)

INSERT INTO Categorii(Titlu,Descriere)
VALUES ('Femei','Produse femei'),('Barbati','produse barbati'),('Copii','produse copii')

INSERT INTO Produse (Denumire,Stock,Pret,Categorie)
VALUES ('Blugi drepti',100,150,1),('Blugi mom',200,150,3),('Pantaloni costum',300,170,2),('Pantaloni scurti',400,130,1),('Pantaloni trening',200,100,2),('Camasa',400,150,1),('Helanca',300,100,2),('Hanorac',250,100,1),('Bluza',300,110,3),('Tricou',270,100,2),('Fusta',200,150,1),('Rochie',100,140,3)

INSERT INTO Comenzi_Produse(Cid,Pid,Cantitate,Pret)
VALUES (1,2,1,150),(3,6,2,400),(2,9,1,250),(2,4,1,300),(4,7,2,300),(4,8,1,100),(5,9,3,300),(5,12,1,150),(5,11,1,100),(6,8,6,600),(6,7,1,150),(7,4,1,170),(7,5,1,130),(7,11,1,100),(8,13,1,140),(8,10,1,110),(8,11,6,600),(9,9,8,800),(9,12,1,150)

INSERT INTO Dimensiuni(Denumire)
VALUES ('xs'),('s'),('m'),('l'),('xl')

INSERT INTO Filtre_produse(Id_produs)
VALUES (2),(3),(4),(5),(6),(7),(8),(9),(10),(11),(12),(13)

INSERT INTO Filtre_Dimensiuni(Id_filtru,Id_dimensiune)
VALUES (1,1),(2,2),(3,3),(4,4),(5,5),(6,1),(7,2),(8,3),(9,4),(10,5),(11,1),(12,2)

INSERT INTO Materiale(Denumire)
VALUES ('bumbac'),('blug'),('satin'),('tricot'),('poliester'),('stofa')

INSERT INTO Culori(Denumire)
VALUES ('alb'),('negru'),('roz'),('albastru'),('rosu'),('crem')

INSERT INTO Filtre_Materiale(Id_filtru,Id_material)
VALUES (1,2),(2,2),(3,6),(4,2),(5,4),(6,1),(7,5),(8,1),(9,3),(10,1),(11,3),(12,5)

INSERT INTO Filtre_Culori(Id_filtru,Id_culoare)
VALUES (1,1),(2,2),(3,4),(4,1),(5,5),(6,6),(7,1),(8,2),(9,3),(10,3),(11,4),(12,6)

INSERT INTO Clienti(Cnp, Nume, Varsta)
VALUES 
(1264569, 'George', 35),
(1264570, 'Carmen', 28),
(1264571, 'Victor', 45),
(1264572, 'Anca', 22);

INSERT INTO Comenzi(DataComanda, Pret_total, Client)
VALUES 
('2024-08-15', 620, 1264569), 
('2024-09-07', 480, 1264570), 
('2024-07-25', 320, 1264571), 
('2024-10-01', 700, 1264572);

INSERT INTO Produse(Denumire, Stock, Pret, Categorie)
VALUES 
('Sacou', 150, 200, 2), 
('Geaca de piele', 100, 300, 1),
('Sandale', 250, 120, 3), 
('Tricou polo', 500, 100, 2),
('Rochie de seara', 75, 350, 1);

INSERT INTO Categorii(Titlu, Descriere)
VALUES 
('Accesorii', 'Accesorii diverse'), 
('Încălțăminte', 'Produse încălțăminte');

INSERT INTO Dimensiuni(Denumire)
VALUES 
('xxs'), 
('xxl');

INSERT INTO Materiale(Denumire)
VALUES 
('piele'), 
('matase');

INSERT INTO Culori(Denumire)
VALUES 
('verde'), 
('gri');

INSERT INTO Filtre_Dimensiuni(Id_filtru, Id_dimensiune)
VALUES 
(12, 6), 
(12, 7);

INSERT INTO Filtre_Materiale(Id_filtru, Id_material)
VALUES 
(12, 7), 
(11, 6); 



SELECT COUNT(Id_produs)AS Produse,Pret
FROM Produse
WHERE Pret>100
GROUP BY Pret 

--1)Categoriile care au mai mult de trei produse a caror stock e mai mare decat 100(GROUP BY,HAVING,WHERE)
SELECT c.Descriere, c.Titlu, COUNT(*) AS Nr_produse
FROM Produse p
INNER JOIN Categorii c ON p.Categorie = c.Id_categorie
WHERE p.Stock > 100
GROUP BY c.Titlu, c.Descriere
HAVING COUNT(*) > 3;


--2)Produsele de culoaarae roz(4 tabele,WHERE)
SELECT p.Denumire, p.Id_produs 
FROM Produse p
INNER JOIN Filtre_produse fp
ON p.Id_produs=fp.Id_produs
INNER JOIN Filtre_Culori fc
ON fc.Id_filtru=fp.Id_filtru
INNER JOIN Culori c
ON c.Id_culoare=fc.Id_culoare
WHERE c.Denumire='roz'

--3)Produsele in marimea s sau xs de culoare crem(6 tabele, WHERE)
SELECT p.Denumire, p.Id_produs,d.Denumire AS Marime 
FROM Produse p
INNER JOIN Filtre_produse fp
ON p.Id_produs=fp.Id_produs
INNER JOIN Filtre_Culori fc
ON fc.Id_filtru=fp.Id_filtru
INNER JOIN Culori c
ON c.Id_culoare=fc.Id_culoare
INNER JOIN Filtre_Dimensiuni fd
ON fd.Id_filtru=fp.Id_filtru
INNER JOIN Dimensiuni d
ON d.Id_dimensiune=fd.Id_dimensiune
WHERE (d.Denumire='s'OR d.Denumire='xs') AND c.Denumire='crem'

--4)Clientii care au comenzi cu minim 2 produse(HAVING,GROUP BY,4 tabele)
SELECT  c.Nume, COUNT(p.Id_produs) AS Nr_produse
FROM Clienti c
INNER JOIN Comenzi cm
ON cm.Client=c.Cnp
INNER JOIN Comenzi_Produse cp
ON cp.Cid=cm.Id_comanda
INNER JOIN Produse p
ON p.Id_produs=cp.Pid
GROUP BY c.Nume
HAVING COUNT(p.Id_produs)>=2

--5)clientii care au in comanda mai mult de 2 produse albe sau negre(WHERE, 7 tabele)
SELECT c.Nume,p.Denumire,cp.Cantitate 
FROM Clienti c
INNER JOIN Comenzi cm
ON c.Cnp=cm.Client
INNER JOIN Comenzi_Produse cp
ON cp.Cid=cm.Id_comanda
INNER JOIN Produse p
ON p.Id_produs=cp.Pid
INNER JOIN Filtre_produse fp
ON fp.Id_produs=p.Id_produs
INNER JOIN Filtre_Culori fc
ON fc.Id_filtru=fp.Id_filtru
INNER JOIN Culori cl
ON cl.Id_culoare=fc.Id_culoare
WHERE (cl.Denumire='alb'OR cl.Denumire='negru') AND cp.Cantitate>=2


--6)produsele ce au fost comandate intr-o cantitate mai mare decat 2(DISTINCT,7 tabele, where)
SELECT DISTINCT p.Denumire, cp.Cantitate
FROM Clienti c
INNER JOIN Comenzi cm
ON c.Cnp=cm.Client
INNER JOIN Comenzi_Produse cp
ON cp.Cid=cm.Id_comanda
INNER JOIN Produse p
ON p.Id_produs=cp.Pid
INNER JOIN Filtre_produse fp
ON fp.Id_produs=p.Id_produs
INNER JOIN Filtre_Dimensiuni fc
ON fc.Id_filtru=fp.Id_filtru
INNER JOIN Dimensiuni cl
ON cl.Id_dimensiune=fc.Id_dimensiune
WHERE cp.Cantitate>=2


--7)produse care nu sunt marimea xl, au culoarea alb sau negru si sunt din blug(where,7 tabele)
SELECT p.Denumire, p.Stock ,c.Denumire
FROM Produse p
INNER JOIN Filtre_produse fp
ON p.Id_produs=fp.Id_produs
INNER JOIN Filtre_Culori fc
ON fc.Id_filtru=fp.Id_filtru
INNER JOIN Culori c
ON c.Id_culoare=fc.Id_culoare
INNER JOIN Filtre_Dimensiuni fd
ON fd.Id_filtru=fp.Id_filtru
INNER JOIN Dimensiuni d
ON d.Id_dimensiune=fd.Id_dimensiune
INNER JOIN Filtre_Materiale fm
ON fm.Id_filtru=fp.Id_filtru
INNER JOIN Materiale m
ON m.Id_material=fm.Id_material
WHERE (d.Denumire!='xl') AND (c.Denumire='negru' OR c.Denumire='alb') AND m.Denumire='blug' 

--8)produsele care nu sunt marimea l si au stockul mai mare decat 100(where,4 tabele)
SELECT p.Denumire, p.Stock ,d.Denumire
FROM Produse p
INNER JOIN Filtre_produse fp
ON p.Id_produs=fp.Id_produs
INNER JOIN Filtre_Dimensiuni fd
ON fd.Id_filtru=fp.Id_filtru
INNER JOIN Dimensiuni d
ON d.Id_dimensiune=fd.Id_dimensiune
WHERE (d.Denumire!='l') AND p.Stock>100

--9)Dimensiunile care apartin unor produse ce au pretul mai mare decat 130
SELECT DISTINCT d.Denumire
FROM Dimensiuni d
INNER JOIN Filtre_Dimensiuni fd ON fd.Id_dimensiune=d.Id_dimensiune
INNER JOIN Filtre_produse fp ON fp.Id_filtru=fd.Id_filtru
INNER JOIN Produse p ON p.Id_produs=fp.Id_produs
WHERE p.Pret>130

--10)Clientii care au cheltuit mai mult de 600 pe toate comenzile
SELECT c.Nume, SUM(cm.Pret_total) AS sumaTotala
FROM CLienti c
INNER JOIN Comenzi cm ON cm.Client=c.Cnp
GROUP BY c.Nume,cm.Pret_total
HAVING SUM(cm.Pret_total)>600



