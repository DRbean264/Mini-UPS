#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <ctime>
#include <pqxx/pqxx>
#include <string>
#include <vector>

#include "Account.hpp"
#include "Item.hpp"
#include "Package.hpp"
#include "Truck.hpp"
#include "WarehouseInfo.hpp"

// #define HOST "localhost"
#define HOST "db"
#define DATABASE "postgres"
#define USER "postgres"
// #define PASSWORD "postgres"
#define PASSWORD "@zxcvbnm123"

class DatabaseConnectionError : public std::exception {
 public:
  virtual const char * what() const noexcept { return "Cannot connect to the database."; }
};

class WareHouseNotExist : public std::exception {
 public:
  virtual const char * what() const noexcept {
    return "Can't find the corresponding warehouse.";
  }
};

class Database {
 public:
  Database();
  ~Database();

  pqxx::connection * connectToDatabase();
  void setup();
  void dropATable(pqxx::connection *, std::string tableName);
  void cleanTables(pqxx::connection *);
  void createTables(pqxx::connection *);
  void insertTables(pqxx::connection * C, SQLObject * object);
  void updateTruck(pqxx::connection * C,
                   truck_status_t status,
                   int x,
                   int y,
                   int truckId);
  void updateTruck(pqxx::connection * C, truck_status_t status, int truckId);
  void updatePackage(pqxx::connection * C, int destX, int destY, int64_t trackingNum);

  void updatePackage(pqxx::connection * C,
                     package_status_t status,
                     int x,
                     int y,
                     int64_t trackingNum);
  void updatePackage(pqxx::connection * C,
                     package_status_t status,
                     int truckid,
                     int64_t trackingNum);
  void updatePackage(pqxx::connection * C, package_status_t status, int64_t trackingNum);
  std::string queryPackageStatus(pqxx::connection * C, int64_t trackingNum);
  int queryAvailableTrucksPerDistance(pqxx::connection * C, int warehouseId);
  bool queryTruckAvailable(pqxx::connection * C, int truckId);
  // pqxx::connection *getConnection();
  vector<int64_t> queryTrackingNumToPickUp(pqxx::connection * C,
                                           int truckid,
                                           int warehouseid);
  int queryWarehouseId(pqxx::connection * C, int x, int y);
  bool queryUpsid(pqxx::connection * C, int64_t upsId);
};

#endif
