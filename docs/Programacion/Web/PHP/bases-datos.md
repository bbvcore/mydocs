---
title: Bases de datos
---
# Bases de datos
## MySQL
### Tipos de conexión
#### Procedural
```php
$conn = mysqli_connect("localhost", "user", "password", "db");
$sql = "Declaración de la consulta a realizar";
$rs = mysqli_query($conn, $sql);
while ($row = mysqli_fetch_assc($rs)){
    echo $row['id'];
}
mysqli_close($conn);
```
#### Orientado a objetos
```php
$conn = new mysqli("localhost", "user", "password", "db");
$sql = "Declaración de la consulta a realizar";
$rs = $conn->query($SQL);
while($row = $result->fetch_assoc){
    echo $row['id'];
}
$conn = close();
```
#### PDO
```php
$pdo = new PDO("mysql:host=localhost;dbname=db","user","password");
$SQL = "Declaración de la consulta a realizar";
$rs = $pdo->query($SQL);
while($row=$rs->fetch(PDO::FETCH_ASSOC)){
    echo $row['id'];
}
```
### Sentencias preparadas
Las sentencias MySQL permiten declarar sentencias preparadas solo con ?, mientras que PDO permite con ? y :
#### Procedural con ?
```php
$SQL = "Select * from users where id=?";
$stmt = mysqli_prepare($con, $SQL);
mysqli_stmt_bind_param($stmt, i, $id);
$id = 10;
$rs = msyqli_stmt_execute($stmt);
while ($row = mysqli_fetch_assc($rs)){
    echo $row['id'];
}
mysqli_close($conn);
```
#### Orientado a objetos
```php
$conn = new mysqli("localhost", "user", "pass", "db");
$stmt = $conn->prepare("SELECT * FROM usuarios WHERE email = ?");
$stmt->bind_param("s", $email);
$email = "email@example.com";
$stmt->execute();
$rs = $stmt->get_result();
while ($row = $rs->fetch_assoc()) {
    echo $row['email'];
}
```
#### PDO
- bindValue(): enlaza el valor en el momento
- bindParam(): enlaza la variable

##### Parámetros posicionales

```php
$pdo = new PDO("mysql:host=localhost;dbname=db", "user", "pass");

$stmt = $pdo->prepare("SELECT * FROM usuarios WHERE id = ? AND estado = ?");

$stmt->bindValue(1, 5, PDO::PARAM_INT);
$stmt->bindValue(2, "activo", PDO::PARAM_STR);

$stmt->execute();

while ($row = $stmt->fetch(PDO::FETCH_ASSOC)) {
    echo $row['nombre'];
}

```

```php
$id = 5;
$estado = "activo";

$stmt = $pdo->prepare("SELECT * FROM usuarios WHERE id = ? AND estado = ?");

$stmt->bindParam(1, $id, PDO::PARAM_INT);
$stmt->bindParam(2, $estado, PDO::PARAM_STR);

$stmt->execute();

```

##### Parámetros nombrados
```php
$stmt = $pdo->prepare("SELECT * FROM usuarios WHERE email = :email AND rol = :rol");

$stmt->bindValue(':email', "test@example.com", PDO::PARAM_STR);
$stmt->bindValue(':rol', "admin", PDO::PARAM_STR);

$stmt->execute();

```

```php
$email = "test@example.com";
$rol = "admin";

$stmt = $pdo->prepare("SELECT * FROM usuarios WHERE email = :email AND rol = :rol");

$stmt->bindParam(':email', $email, PDO::PARAM_STR);
$stmt->bindParam(':rol', $rol, PDO::PARAM_STR);

$stmt->execute();
```


