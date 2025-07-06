<?php
$mysqli = new mysqli("localhost", "root", "", "aair3467");

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $nume = $_POST["nume"];
    $comentariu = $_POST["comentariu"];

    $stmt = $mysqli->prepare("INSERT INTO comentarii (nume, comentariu) VALUES (?, ?)");
    $stmt->bind_param("ss", $nume, $comentariu);
    $stmt->execute();

    echo "<p>Comentariul a fost trimis pentru aprobare.</p>";
}

$comentarii = $mysqli->query("SELECT * FROM comentarii WHERE aprobat = 1 ORDER BY data_adaugarii DESC");
?>

<!DOCTYPE html>
<html>
<head>
    <title>Tiramisu cu mascarpone și frișcă, fără ou</title>
</head>
<body>
<h1>
    Tiramisu cu mascarpone și frișcă, fără ou
</h1>
<p>Ingrediente (10 porții)
    500 ml - cafea
    1 sticluță - esență de rom
    120 g - zahăr pudră
    500 ml - frișcă lichidă
    800 g - pișcoturi
    cacao pentru decor
    500 g - mascarpone
    1 linguriță extract de vanilie
    Preparare
    1
    Se pregătește cafeaua și se lasă la răcit.

    2
    Când s-a răcit, se adaugă esența de rom și se amestecă.

    3
    Într-un bol mare se amestecă mascarpone (rece de la frigider) cu zahărul pudră și extractul de vanilie până când se obține o compoziție omogenă.

    4
    Într-un alt bol se bate frișca lichidă (rece, de la frigider) până când se întărește.

    5
    Se adaugă treptat frișca bătută în mascarpone, cu mișcări lente și circulare până se omogenizează.

    6
    Se înmoaie fiecare pișcot pentru câteva secunde, în cafeaua răcită.

    7
    Se așează într-un vas un strat de pișcoturi înmuiate, un strat generos de cremă de mascarpone cu frișcă, alternând între straturi de pișcoturi și straturi de cremă până când se termină ingredientele.

    8
    Ultimul strat trebuie să fie de cremă.

    9
    Se presară din plin cacao pentru un aspect final, delicios.

    10
    Se acoperă și se lasă la frigider peste noapte.</p>

<h3>Comentarii:</h3>
<?php while ($row = $comentarii->fetch_assoc()): ?>
    <p><strong><?= htmlspecialchars($row["nume"]) ?></strong>: <?= nl2br(htmlspecialchars($row["comentariu"])) ?></p>
<?php endwhile; ?>

<h3>Adaugă comentariu:</h3>
<form method="POST">
    Nume: <input type="text" name="nume" required><br>
    Comentariu: <br>
    <textarea name="comentariu" rows="4" cols="50" required></textarea><br>
    <input type="submit" value="Trimite">
</form>
</body>
</html>
