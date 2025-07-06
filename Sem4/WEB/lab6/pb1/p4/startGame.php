<?php
session_start();

include './base.php';
$game = generateBoard();

$_SESSION['game'] = $game;

show($game);

?>