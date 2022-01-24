'''
* Oz Shlomi Amoyal
* ex_7
'''
from my_plot import plot

class Date:
    
    #initializing Date with day(valid values 1-31) month(valid values 1-12) year (valid values year>1900)
   
    def __init__(self,day,month,year):
        self.day=day
        self.month=month
        self.year=year
class Person:
    #initializing person with firstName,lastName,date,height and weight
    def __init__(self,firstName,lastName,date,height,weight):
        self.firstName=firstName
        self.lastName=lastName
        self.date=date
        self.height=height
        self.weight=weight

'''
* Function Name:load
* Input:inputFile(file name),persons (array to load data into)
* Output:none
* Function Operation:gets a file to read from and loads the data into a Person array,and updates the counter of persons
'''     
def load(input_file,persons):
    #open file in read mode
    file = open(input_file, "r")
    #seperating variable
    seperator=','
    #for every line in the file a person object is created with the init function
    for line in file:
        line=line[:-1]
        splitLine=line.split(seperator)
        dateOfBirth=Date(splitLine[2],splitLine[3],splitLine[4])
        #enter the person created to the persons array
        persons.append(Person(splitLine[0],splitLine[1],dateOfBirth,splitLine[5],"{:.2f}".format(float(splitLine[6]))))
    file.close()

'''
* Function Name:save
* Input:output_file(file name),persons (array to load data into)
* Output:none
* Function Operation:exports data from the persons array into a text file
'''
def save(output_file,persons):
    #open/create file in write mode
    file = open(output_file, "w")
    #seperating variable
    seperator=','
    #for every person object in the persons array
    for person in persons:
        #create a string that contains the information seperated by ','
        row=''
        row+=(person.firstName+',')
        row+=(person.lastName+',')
        row+=(person.date.day+',')
        row+=(person.date.month+',')
        row+=(person.date.year+',')
        row+=(person.height+',')
        row+=(person.weight+'\n')
        #write the line in the file
        file.write(row)

    file.close()

'''
* Function Name:comparePersonByBMI
* Input:persons(persons array),i(first person index),j(second person index)
* Output:0 or 1
* Function Operation:calculates and compares 2 persons from the array by BMI,if first has a smaller BMI value
                    the function returns 1 else returns zero
'''
def comparePersonByBMI(persons,i,j):
    #calculate both BMIs
    personIHeightinM=float(persons[i].height)/100
    personIBmi=float(persons[i].weight)/(personIHeightinM**2)
    personJHeightinM=float(persons[j].height)/100
    personJBmi=float(persons[j].weight)/(personJHeightinM**2)
    #compare BMI values
    if(personIBmi<personJBmi):
        return 1
    return 0
    
'''
* Function Name:comparePersonByHeight
* Input:persons (persons array),i(first person index),j(second person index)
* Output:0 or 1
* Function Operation:compares 2 persons from the array by Height,if first is higher
                    the function returns 1 else returns zero
'''
def comparePersonByHeight(persons,i,j):
    if(float(persons[i].height)<float(persons[j].height)):
        return 1
    return 0

'''
* Function Name:comparePersonByWeight
* Input:persons (persons array), i(first person index), j(second person index)
* Output:0 or 1
* Function Operation:compares 2 persons from the array by Weight,if first weighs less
                    the function returns 1 else returns zero
'''
def comparePersonByWeight(persons,i,j):
    if(float(persons[i].weight)<float(persons[j].weight)):
        return 1
    return 0

'''
* Function Name:comparePersonByFirstName
* Input:persons,i(first person index),j(second person index)
* Output:0 or 1
* Function Operation:compares 2 persons from the array by lexicographic value of firstName,if first has smaller value
'''
def comparePersonByFirstName(persons,i,j):
    if(str(persons[i].firstName)<str(persons[j].firstName)):
        return 1
    return 0

'''
* Function Name:comparePersonByLastName
* Input:persons(persons array),i(first person index),j(second person index)
* Output:0 or 1
* Function Operation:compares 2 persons from the array by lexicographic value of lastName,if first has smaller value
                    the function returns 1 else returns zero
'''
def comparePersonByLastName(persons,i,j):
    if(str(persons[i].lastName)<str(persons[j].lastName)):
        return 1
    return 0

'''
* Function Name:comparePersonByDate
* Input:persons (persons array), i(first person index),j(second person index)
* Output:0 or 1
* Function Operation:compares 2 persons from the array by DateOfBirth, if the first person is older
                    the function returns 1 else returns zero
'''
def comparePersonByDate(persons,i,j):
    if(int(persons[i].date.year)<int(persons[j].date.year)):
        return 1
    if(int(persons[i].date.year)==int(persons[j].date.year)):
        if(int(persons[i].date.month)<int(persons[j].date.month)):
            return 1
        if(int(persons[i].date.month)==int(persons[j].date.month)):
            if(int(persons[i].date.day)<int(persons[j].date.day)):
                return 1
    return 0


def quicksort(persons,start,stop,compare):
    if(start>=stop-1):
        return
    pivot=start
    j=start
    for i in range(start+1,stop):
        if(compare(persons,i,pivot)==1):
            j+=1
            if(i!=j):
                persons[i],persons[j]=persons[j],persons[i]
    persons[start],persons[j]=persons[j],persons[start]
    quicksort(persons,start,j,compare)
    quicksort(persons,j+1,stop,compare)
    

input_file = 'persons.txt'
byFirstNameFile='by_first_name.csv'
byLastNameFile='by_last_name.csv'
byDateFile='by_date.csv'
byHeightFile='by_height.csv'
byWeightFile='by_weight.csv'
byBMIFile='by_BMI.csv'
persons=[]
load(input_file,persons)
plot('Input:', input_file)

quicksort(persons,0,int(len(persons)),comparePersonByFirstName)
save(byFirstNameFile,persons)
plot('By first name:',byFirstNameFile)


quicksort(persons,0,int(len(persons)),comparePersonByLastName)
save(byLastNameFile,persons)
plot('By last name:',byLastNameFile)

quicksort(persons,0,int(len(persons)),comparePersonByDate)
save(byDateFile,persons)
plot('By date:',byDateFile)

quicksort(persons,0,int(len(persons)),comparePersonByHeight)
save(byHeightFile,persons)
plot('By height:',byHeightFile)


quicksort(persons,0,int(len(persons)),comparePersonByWeight)
save(byWeightFile,persons)
plot('By weight:',byWeightFile)


quicksort(persons,0,int(len(persons)),comparePersonByBMI)
save(byBMIFile,persons)
plot('By bmi:',byBMIFile)





