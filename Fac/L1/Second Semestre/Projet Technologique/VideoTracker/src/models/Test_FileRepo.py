from Point_FileRepo import *
import unittest
import pathlib

class TestPoint(unittest.TestCase):
  
    def setUp(self):
        self.__timeTable = [0.0, 0.5, 1.0]
        self.__point1_1 = Point(0, 0)
        self.__point1_2 = Point(1, 1)
        self.__point1_3 = Point(2, 2)
        self.__point2_1 = Point(-1, -2)
        self.__point2_2 = Point(-1, -3)
        self.__point2_3 = Point(-2, -4)
        self.__point3_1 = Point(1.111, 2.222)
        self.__point3_2 = Point(2.222, 2.222)
        self.__point3_3 = Point(3.333, 4.444)
        self.__csv1 = open("csv_test1.csv", "r")
        self.__csv2 = open("csv_test2.csv", "r")
        self.__csv3 = open("csv_test3.csv", "r")
        self.__str1 = "time = 0.0, x = 0, y = 0;\ntime = 0.5, x = 1, y = 1;\ntime = 1.0, x = 2, y = 2;"
        self.__str2 = "time = 0.0, x = -1, y = -2;\ntime = 0.5, x = -1, y = -3;\ntime = 1.0, x = -2, y = -4;"
        self.__str3 = "time = 0.0, x = 1.111, y = 2.222;\ntime = 0.5, x = 2.222, y = 2.222;\ntime = 1.0, x = 3.333, y = 4.444;"
        self.csv_try1 = FileRepo(pathlib.Path(__file__).parent.resolve())
        self.csv_try2 = FileRepo(pathlib.Path(__file__).parent.resolve())
        self.csv_try3 = FileRepo(pathlib.Path(__file__).parent.resolve())
        
    def testExportCSV(self):
        self.csv_test1 = self.csv_try1.exportDataToCSV(self.__timeTable, [self.__point1_1, self.__point1_2, self.__point1_3], "csv_test1_result.csv")
        self.csv1Tamer = open("csv_test1_result.csv", "r")
        self.assertTrue(self.__csv1 == self.__csv1Tamer)
        self.csv_test2 = self.csv_try2.exportDataToCSV(self.__timeTable, [self.__point2_1, self.__point2_2, self.__point2_3], "csv_test2_result.csv")
        self.assertTrue(self.__csv2 == open("csv_test2_result.csv", "r"))
        self.csv_test3 = self.csv_try3.exportDataToCSV(self.__timeTable, [self.__point3_1, self.__point3_2, self.__point3_3], "csv_test3_result.csv")
        self.assertTrue(self.__csv3 == open("csv_test3_result.csv", "r"))
        
    def testExportString(self):
        self.str_test1 = self.csv_try1.exportDataToString(self.__timeTable, [self.__point1_1, self.__point1_2, self.__point1_3])
        print(self.str_test1)
        print(self.__str1)
        self.assertTrue(self.__str1 == self.str_test1)
        self.str_test2 = self.csv_try2.exportDataToString(self.__timeTable, [self.__point2_1, self.__point2_2, self.__point2_3])
        self.assertTrue(self.__str1 == self.str_test1)
        self.str_test3 = self.csv_try3.exportDataToString(self.__timeTable, [self.__point3_1, self.__point3_2, self.__point3_3])
        self.assertTrue(self.__str3 == self.str_test3)
        
if __name__ == '__main__':
    unittest.main()