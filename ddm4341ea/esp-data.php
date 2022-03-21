<!DOCTYPE html>
<html><body>
<?php
/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-esp8266-mysql-database-php/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

$servername = "localhost";

// REPLACE with your Database name
$dbname = "ddm4341ea";
// REPLACE with Database user
$username = "root";
// REPLACE with Database user password
$password = "";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 

$sql = "SELECT id, nA, nB, nC, mA, mB, mC FROM readings ORDER BY id DESC";

echo '<table cellspacing="5" cellpadding="5">
      <tr> 
        <td>ID</td>
        <td>nA</td> 
        <td>nB</td>
        <td>nC</td>
        <td>mA</td>
        <td>mB</td>
        <td>mC</td>
      </tr>';
 
if ($result = $conn->query($sql)) {
    while ($row = $result->fetch_assoc()) {
        $row_id = $row["id"];
        $row_value1 = $row["nA"];
        $row_value2 = $row["nB"];
        $row_value3 = $row["nC"];
        $row_value4 = $row["mA"];
        $row_value5 = $row["mB"];
        $row_value6 = $row["mC"];
      
        echo '<tr> 
                <td>' . $row_id . '</td>
                <td>' . $row_value1 . '</td> 
                <td>' . $row_value2 . '</td>
                <td>' . $row_value3 . '</td>
                <td>' . $row_value4 . '</td> 
                <td>' . $row_value5 . '</td>
                <td>' . $row_value6 . '</td>
              </tr>';
    }
    $result->free();
}

$conn->close();
?> 
</table>
</body>
</html>
