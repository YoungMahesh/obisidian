```bash
# Start, Stop localhost mongodb
sudo systemctl start mongod    # start mongodb 
sudo systemctl status mongod   # verify if mongodb has started successfully
sudo systemctl stop mongod     # stop mongodb


# Mongo Shell
mongo         # go into mongodb-shell
db            # show current database we are using
show dbs      # list databases
use databaseName # switch to a different database
# You do not need to create the database before you switch. 
# MongoDB creates the database when you first store data in that database (such as create the first collection in the database).

show collections           # check tables in the current database
db.collectionName.find()   # check content of the mongodb collection
db.collectionName.remove({})      #  deletes all data from the collection
db.dropDatabase()   # delete current database


# dump == backup
# https://www.mongodb.com/docs/database-tools/mongodump/
mongodump --uri="Uri-of-database" # dump from remote mongodb
mongodump  # dump all databases in the current directory from local database
mongodump -d databaseName   # dump single database from local database
mongodump -d databaseName -c collectionName   # dump single collection from local database

# https://www.mongodb.com/docs/database-tools/mongorestore/
mongorestore <backup-folder>  # restore all databases
mongorestore <backup-folder> --uri="mongodb-uri"  # resotre all databases in remote mongodb
mongorestore -d defineDatabaseName /backupFolderName/   # restore a database
mongorestore -d databaeName -c defineCollectionName /backupFolder/collection1.bson  # restore a collection
```
