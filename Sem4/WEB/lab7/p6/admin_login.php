<?php
session_start();
$mysqli = new mysqli("localhost", "root", "", "aair3467");

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $user = $_POST["user"];
    $pass = md5($_POST["pass"]);

    $stmt = $mysqli->prepare("SELECT * FROM admini WHERE user = ? AND parola = ?");
    $stmt->bind_param("ss", $user, $pass);
    $stmt->execute();
    $res = $stmt->get_result();

    if ($res->num_rows > 0) {
        $_SESSION["admin"] = true;
        header("Location: admin_moderare.php");
        exit;
    } else {
        echo "Autentificare eșuată.";
    }
}
?>

<form method="POST">
    Utilizator: <input type="text" name="user"><br>
    Parola: <input type="password" name="pass"><br>
    <input type="submit" value="Autentificare">
</form>
