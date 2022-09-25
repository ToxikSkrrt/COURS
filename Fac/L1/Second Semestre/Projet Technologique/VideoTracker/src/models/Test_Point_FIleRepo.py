from Point_FileRepo import *
import unittest
import filecmp

class TestPoint_FileRepo(unittest.TestCase):
  
    def setUp(self):
        self.__point1 = Point(0, 0)
        self.__point2 = Point(-1, -2)
        self.__point3 = Point(1, 2)
        self.__point4 = Point(1.111, 2.222)
        self.__point5 = Point(-1.111, -2.222)
        
        self.__points = [self.__point1, self.__point2, self.__point3, self.__point4, self.__point5]
        self.__timeTable = [0.0, 1.0, 2.0, 3.0, 4.0]
        
        self.__fileUnittestCreation = FileRepo('')
        self.__fileUnittestCreation.exportDataToCSV(self.__timeTable, self.__points, 'CSV_Unittest.csv')
        self.__fileUnittestCreation.exportDataToTXT(self.__timeTable, self.__points, 'TXT_Unittest.txt')
        
        self.__str = self.__fileUnittestCreation.exportDataToString(self.__timeTable, self.__points)
        self.__strToTXT = open('STR_Unittest.txt', 'w')
        self.__strToTXT.write(self.__str)
        self.__strToTXT.close()
        
    def testXGet(self):
        self.assertTrue(self.__point1.xGet() == self.__point1.x)
        self.assertTrue(self.__point2.xGet() == self.__point2.x)
        self.assertTrue(self.__point3.xGet() == self.__point3.x)
        self.assertTrue(self.__point4.xGet() == self.__point4.x)
        self.assertTrue(self.__point5.xGet() == self.__point5.x)
        
    def testYGet(self):
        self.assertTrue(self.__point1.yGet() == self.__point1.y)
        self.assertTrue(self.__point2.yGet() == self.__point2.y)
        self.assertTrue(self.__point3.yGet() == self.__point3.y)
        self.assertTrue(self.__point4.yGet() == self.__point4.y)
        self.assertTrue(self.__point5.yGet() == self.__point5.y)
        
    def testXSet(self):
        self.__point1.xSet(self.__point2.xGet())
        self.assertTrue(self.__point1.xGet() == self.__point2.xGet())
        self.__point2.xSet(self.__point3.xGet())
        self.assertTrue(self.__point2.xGet() == self.__point3.xGet())
        self.__point3.xSet(self.__point4.xGet())
        self.assertTrue(self.__point3.xGet() == self.__point4.xGet())
        self.__point4.xSet(self.__point5.xGet())
        self.assertTrue(self.__point4.xGet() == self.__point5.xGet())
    
    def testYSet(self):
        self.__point1.ySet(self.__point2.yGet())
        self.assertTrue(self.__point1.yGet() == self.__point2.yGet())
        self.__point2.ySet(self.__point3.yGet())
        self.assertTrue(self.__point2.yGet() == self.__point3.yGet())
        self.__point3.ySet(self.__point4.yGet())
        self.assertTrue(self.__point3.yGet() == self.__point4.yGet())
        self.__point4.ySet(self.__point5.yGet())
        self.assertTrue(self.__point4.yGet() == self.__point5.yGet())
        
    def testExportDataToCSV(self):
        self.assertTrue(filecmp.cmp('myCSV.csv', 'CSV_Unittest.csv'))
        
    def testExportDataToStringAndTXT(self):
        self.assertTrue(filecmp.cmp('TXT_Unittest.txt', 'STR_Unittest.txt'))
        
    
if __name__ == '__main__':
    unittest.main()