<?php
/*
  
    For iOS retrieve data

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

$sql = "SELECT id, nA, nB, nC, mA, mB, mC FROM readings ORDER BY id DESC LIMIT 1";
 
if ($result = $conn->query($sql)) {
    while ($row = $result->fetch_assoc()) {
        $row_id = $row["id"];
        $row_value1 = $row["nA"];
        $row_value2 = $row["nB"]; 
        $row_value3 = $row["nC"]; 
        $row_value4 = $row["mA"];
        $row_value5 = $row["mB"]; 
        $row_value6 = $row["mC"]; 
      
        // if ($row_value1 == "1" && $row_value2 == "1" && $row_value3 == "1") {
        //     //User $username: password match
        //     echo '1';
        // }elseif ($row_value1 == "1" && $row_value2 == "1" && $row_value3 == "0") {
        //     //User $username: password match
        //     echo '2';
        // }elseif ($row_value1 == "1" && $row_value2 == "0" && $row_value3 == "0") {
        //     //User $username: password match
        //     echo '3';
        // }elseif ($row_value1 == "0" && $row_value2 == "1" && $row_value3 == "1") {
        //     //User $username: password match
        //     echo '4';
        // }elseif ($row_value1 == "0" && $row_value2 == "0" && $row_value3 == "1") {
        //     //User $username: password match
        //     echo '5';
        // }elseif ($row_value1 == "0" && $row_value2 == "1" && $row_value3 == "0") {
        //     //User $username: password match
        //     echo '6';
        // }elseif ($row_value1 == "1" && $row_value2 == "0" && $row_value3 == "1") {
        //     //User $username: password match
        //     echo '7';
        // }else {
        //     //User $username: password match
        //     echo '0';
        // }

        echo "$row_value1$row_value2$row_value3$row_value4$row_value5$row_value6";

    }
    $result->free();
}

$conn->close();
?>
