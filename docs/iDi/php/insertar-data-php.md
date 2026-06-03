---
title: Insertar data con Php
---
# Insertar data con Php
```php
<?php
// 1. Conexión a SQL Server mediante PDO
$server = "192.168.10.200";
$database = "Runtime";
$user = "sa";
$password = "SQLserver_2026";

try {
    // Nota: TrustServerCertificate=true se pasa en el DSN
    $dsn = "sqlsrv:Server=$server;Database=$database;TrustServerCertificate=true";
    $conn = new PDO($dsn, $user, $password);
    $conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
} catch (PDOException $e) {
    die("Error de conexión en SQL Server: " . $e->getMessage() . "\n");
}

// 2. Configuración de la simulación
$tags = ["Sensor_Temperatura_01", "Presion_Bomba_A", "Flujo_Agua_Principal"];
$cantidad = 50;

echo "Insertando $cantidad registros en SQL Server desde PHP...\n";

try {
    // Iniciamos transacción para inserción masiva rápida
    $conn->beginTransaction();

    $sql = "INSERT INTO Runtime.dbo.AnalogLive (
                DateTime, TagName, Value, Quality, QualityDetail, OPCQuality, wwVersion, wwRetrievalMode
            ) VALUES (?, ?, ?, ?, ?, ?, ?, ?)";
    
    $stmt = $conn->prepare($sql);

    for ($i = 0; $i < $cantidad; $i++) {
        $dateTime = date("Y-m-d H:i:s");
        $tagName = $tags[array_rand($tags)];
        $value = mt_rand(1000, 9500) / 100; // Genera un float aleatorio (10.00 a 95.00)
        
        $stmt->execute([
            $dateTime,
            $tagName,
            $value,
            192, // Quality
            0,   // QualityDetail
            192, // OPCQuality
            1,   // wwVersion
            "Full" // wwRetrievalMode
        ]);
        
        usleep(10000); // 10 milisegundos de delay opcional
    }

    $conn->commit();
    echo "¡Inserción completada con éxito!\n";

} catch (Exception $e) {
    $conn->rollBack();
    echo "Error al insertar datos: " . $e->getMessage() . "\n";
}

?>
```