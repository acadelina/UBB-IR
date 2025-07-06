<?php
$baseDir = realpath(__DIR__ . '/root');
$pathParam = isset($_GET['path']) ? $_GET['path'] : '.';
$requestedPath = realpath($baseDir . DIRECTORY_SEPARATOR . $pathParam);

if ($requestedPath === false || strpos($requestedPath, $baseDir) !== 0 || !is_dir($requestedPath)) {
    http_response_code(400);
    echo json_encode([]);
    exit;
}

$items = [];
foreach (scandir($requestedPath) as $entry) {
    if ($entry === '.' || $entry === '..') continue;
    $fullPath = $requestedPath . DIRECTORY_SEPARATOR . $entry;
    $items[] = [
        'name' => $entry,
        'type' => is_dir($fullPath) ? 'dir' : 'file',
        'path' => substr($fullPath, strlen($baseDir) + 1)
    ];
}

header('Content-Type: application/json');
echo json_encode($items);
