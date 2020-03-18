# Part. 1
#=======================================
# Import module
#  csv -- fileIO operation
import csv
#=======================================

# Part. 2
#=======================================
# Read cwb weather data
cwb_filename = '106061151.csv'
data = []
header = []
with open(cwb_filename) as csvfile:
   mycsv = csv.DictReader(csvfile)
   header = mycsv.fieldnames
   for row in mycsv:
      data.append(row)
#=======================================

# Part. 3
#=======================================
station_id = ["C0A880", "C0F9A0", "C0G640", "C0R190", "C0X260"]
ans = []

for i in station_id: 
    # Analyze data depend on your group and store it to target_data like:
    # Retrive all data points which station id is "C0X260" as a list.
    target_data = list(filter(lambda item: item['station_id'] == i, data))
    
    # Retrive ten data points from the beginning.
    # target_data = data[:10]
    
    sum = 0
    n = 0
    
    for j in target_data:
        if j['PRES'] != '-99.000' and j['PRES'] != '-999.000':
            sum += float(j['PRES'])
            n += 1
    
    if n == 0:
        ans.append([i, 'None'])
    else:
        ans.append([i, sum/n])

#=======================================

# Part. 4
#=======================================
# Print result
print(ans)
#========================================