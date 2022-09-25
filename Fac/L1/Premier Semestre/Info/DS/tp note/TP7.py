class Date:
    DAYS = ["Monday", "Tuesday", "Wednesday", "Thursday", "Saturday", "Sunday"]
    MONTHS = ["January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"]
    MONTHCODE = [6, 2, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4]
    
    def __init__(self, year, month, day):
        self.year = year
        self.month = month
        self.day = day
    
    def getYear(self):
        return self.year
    
    def getMonth(self):
        return self.month
    
    def getDay(self):
        return self.day
    
    def getNameMonth(self):
        return Date.MONTHS[self.month - 1]
    
    def getNameDay(self):
        return 
    
    def setYear(self, year):
        self.year = year
        
    def setMonth(self, month):
        self.month = month
        
    def setDay(self, day):
        self.day = day
    
    def isLeapYear(self):
        if self.year % 400 == 0 or (self.year % 4 == 0 and self.year % 100 != 0):
            return True
        else:
            return False
            
    def yearCode(self):
        year = self.year
        year -= 2000
        year += year % 400 == 0 or (year % 4 == 0 and year % 100 != 0)
        
    
if __name__ == '__main__':
    date = Date(2021, 12, 6)
    print(date.getDay())
    date.setDay(17)
    print(date.getDay())