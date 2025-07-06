<?php
$baseDir = realpath(__DIR__ . '/root');
if (!isset($_GET['file'])) {
    http_response_code(400);
    exit('No file specified.');
}

$fileParam = $_GET['file'];
$filePath = realpath($baseDir . DIRECTORY_SEPARATOR . $fileParam);

if ($filePath === false || strpos($filePath, $baseDir) !== 0 || !is_file($filePath)) {
    http_response_code(404);
    exit('File not found.');
}

$ext = strtolower(pathinfo($filePath, PATHINFO_EXTENSION));
$mimeTypes = [
    'png' => 'image/png',
    'jpg' => 'image/jpeg',
    'jpeg' => 'image/jpeg',
    'gif' => 'image/gif',
    'bmp' => 'image/bmp',
    'svg' => 'image/svg+xml',
    'txt' => 'text/plain',
    'php' => 'text/plain',
    'html' => 'text/html',
];

if (isset($mimeTypes[$ext])) {
    header('Content-Type: ' . $mimeTypes[$ext]);
} else {
    header('Content-Type: application/octet-stream');
}

if (strpos($mimeTypes[$ext] ?? '', 'text/') === 0 || in_array($ext, ['php', 'html'])) {
    // Escape for safety in HTML viewer
    echo htmlspecialchars(file_get_contents($filePath));
} else {
    readfile($filePath);
}
