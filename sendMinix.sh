cd ./onlyChangedFilesMinix
./copy_dead_test.sh
cd ..
diff -rupNEZbB minixDeadCleanFiles/usr/ minixDeadTest/usr/ > am406133.patch
scp -P 2226 am406133.patch root@localhost:/
scp -P 2226 runInstall.sh root@localhost:/
