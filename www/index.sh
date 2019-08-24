echo "<HTML>"
echo "<h1>Hello world!</h1>"
thisIp=$(hostname -i | awk '{ print $1}')
echo "<p>Clyth running on $thisIp!</p>"
echo "</HTML>"
