<?php
session_start();
mysqli_report(MYSQLI_REPORT_ERROR | MYSQLI_REPORT_STRICT);
$mysqli = new mysqli("localhost", "root", "", "aair3467");

$logged = isset($_SESSION["logged"]) ? $_SESSION["logged"] : false;

if(isset($_POST["act"])) {
    if($_POST["act"]=="Login"){
        $user = mysqli_real_escape_string($mysqli, $_POST["user"]);
        $pass = md5(mysqli_real_escape_string($mysqli, $_POST["pass"]));
        if(mysqli_num_rows($mysqli->query("SELECT * FROM `useri` WHERE `user`='{$user}' AND `pass`='{$pass}'"))>0){
            $r  = mysqli_fetch_assoc($mysqli->query("SELECT * FROM `useri` WHERE `user`='{$user}' AND `pass`='{$pass}'"));

            $_SESSION["logged"] = true;
            $_SESSION["user"] = $user;
            $_SESSION["pp"] = $r["pp64"];
            echo $pp;
            header("Refresh:0");
        }

    }
    else if($_POST["act"]=="Logout"){
        $_SESSION["logged"] = false;
        echo $logged;
        header("Refresh:0");
    }
    else if($_POST["act"]=="UploadPic"){
        foreach ($_FILES['ppic']['tmp_name'] as $index => $tmpName) {
            if (is_uploaded_file($tmpName)) {
                $img = "data:image/jpg;base64," . base64_encode(file_get_contents($tmpName));
                $stmt = $mysqli->prepare("INSERT INTO poze (user, fisier) VALUES (?, ?)");
                $stmt->bind_param("ss", $_SESSION["user"], $img);
                $stmt->execute();
            }
        }
    }
    else if($_POST["act"]=="ClearPic"){
        $pp="";
        $mysqli->query("UPDATE `useri` SET `pp64`='$pp' WHERE `user`='{$_SESSION["user"]}'");
        $_SESSION["pp"] = $pp;
    }

}
?>

<html>
<head></head>

<body>
<?php if(!$logged) { ?>
    <h2>Login</h2>
    <form action="#" method="POST">
        Username <input type="text" name="user"><br/>
        Password <input type="password" name="pass"><br/>
        <input type="submit" name="act" value="Login">
    </form>
<?php } else { ?>
    <?php echo $_SESSION["user"];?>
    <img src="<?php echo $_SESSION["pp"];?>">
    <h3>Pozele tale:</h3>
    <?php
    $user = $_SESSION["user"];
    $res = $mysqli->query("SELECT fisier FROM poze WHERE user='$user'");
    while ($row = $res->fetch_assoc()) {
        echo "<img src='{$row['fisier']}' width='150' style='margin:5px;'>";
    }
    ?>

    <form action="#" method="POST" enctype="multipart/form-data">
        <input type="file" name="ppic[]" accept=".jpg, .jpeg, .png" multiple>
        <input type="submit" name="act" value="UploadPic">
        <input type="submit" name="act" value="ClearPic">
    </form>

    <form action="viewall.php" method="GET" style="margin-top:10px;">
        <button type="submit">Vezi toate profilurile</button>
    </form>


    <form action="#" method="POST">
        <input type="submit" name="act" value="Logout">
    </form>

<?php } ?>
</body>
</html>