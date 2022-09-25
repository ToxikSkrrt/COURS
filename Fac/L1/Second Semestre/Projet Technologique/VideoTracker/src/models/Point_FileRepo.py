import os

class Point:

    def __init__(self, x : float, y : float):
        self.x = x
        self.y = y
  
    def xGet(self):
        return self.x

    def yGet(self):
        return self.y

    def xSet(self, x_value : float):
        self.x = x_value

    def ySet(self, y_value : float):
        self.y = y_value


class FileRepo:
  
    def __init__(self, path : str):
        self.path = path #os.path.dirname(path) pour var path

    def exportDataToString(self, dataTimes : list, dataPoints : list) -> str:
        strExport = ""
        if len(dataPoints) == len(dataTimes):
            for i in range(len(dataPoints)):
                Time = dataTimes[i]
                X_Coord = dataPoints[i].xGet()
                Y_Coord = dataPoints[i].yGet()
                strExport += f'time = {Time}, x = {X_Coord}, y = {Y_Coord};\n'
            return strExport
        
    def exportDataToTXT(self, dataTimes : list, dataPoints : list, fileName : str) -> None:
        strExport = ""
        if len(dataPoints) == len(dataTimes):
            for i in range(len(dataPoints)):
                Time = dataTimes[i]
                X_Coord = dataPoints[i].xGet()
                Y_Coord = dataPoints[i].yGet()
                strExport += f'time = {Time}, x = {X_Coord}, y = {Y_Coord};\n'
            file = open(fileName, "w")
            file.write(strExport)
            file.close()

    def exportDataToCSV(self, dataTimes : list, dataPoints : list, fileName : str) -> None:
        if len(dataPoints) == len(dataTimes):
            file = open(fileName, "w")
            for i in range(len(dataPoints)):
                Time = dataTimes[i]
                X_Coord = dataPoints[i].xGet()
                Y_Coord = dataPoints[i].yGet()
                file.write(f'{Time},{X_Coord},{Y_Coord}\n')
            file.close()
        