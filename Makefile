OBJ = AcceptAppUI.o AdminOptionUI.o AllAssignedUI.o AllPendingUI.o AllReportsUI.o Application.o Course.o CourseInfoUI.o CourseQueue.o GenInfo.o GradApp.o GradAppFormUI.o GradAppQueue.o GradInfoQueue.o Graduate.o main.o Manager.o OneAssignedUI.o OnePendingUI.o OneReportUI.o SelectAppUI.o SelectCrsUI.o SelectEditUI.o SelectEntryUI.o StuAppFormUI.o StuNumUI.o StuOptionUI.o SubmitAppUI.o TACourse.o TACourseInfoUI.o TACourseQueue.o TakenCourse.o TakenCourseInfoUI.o TakenCourseQueue.o Tools.o UGradInfoQueue.o UGradApp.o UGradAppQueue.o Undergraduate.o WelcomeUI.o WorkExp.o WorkExpQueue.o WorkExpUI.o

CPPFILES = AcceptAppUI.cpp AdminOptionUI.cpp AllAssignedUI.cpp AllPendingUI.cpp AllReportsUI.cpp Application.cpp Course.cpp CourseInfoUI.cpp CourseQueue.cpp GenInfo.cpp GradApp.cpp GradAppFormUI.cpp GradAppQueue.cpp GradInfoQueue.cpp Graduate.cpp main.cpp Manager.cpp OneAssignedUI.cpp OnePendingUI.cpp OneReportUI.cpp SelectAppUI.cpp SelectCrsUI.cpp SelectEditUI.cpp SelectEntryUI.cpp StuAppFormUI.cpp StuNumUI.cpp StuOptionUI.cpp SubmitAppUI.cpp TACourse.cpp TACourseInfoUI.cpp TACourseQueue.cpp TakenCourse.cpp TakenCourseInfoUI.cpp TakenCourseQueue.cpp test.cpp Tools.cpp UGradInfoQueue.cpp UGradApp.cpp UGradAppQueue.cpp Undergraduate.cpp WelcomeUI.cpp WorkExp.cpp WorkExpQueue.cpp WorkExpUI.cpp

TXT = majors.txt jobs.txt lastAppNum.txt courses.txt info.txt date.txt faculty.txt research.txt Applications AppSummaries

OBJ2 = test.o WorkExp.o



testPgm:	$(OBJ2)
		g++ -o testPgm $(OBJ2) 

cutaes:		$(OBJ)
		g++ -o cutaes $(OBJ) `pkg-config gtkmm-3.0 --cflags --libs`

AcceptAppUI.o:	AcceptAppUI.cpp AcceptAppUI.h
		g++ -c AcceptAppUI.cpp `pkg-config gtkmm-3.0 --cflags --libs`

AdminOptionUI.o:	AdminOptionUI.cpp AdminOptionUI.h 
		g++ -c AdminOptionUI.cpp `pkg-config gtkmm-3.0 --cflags --libs`

AllAssignedUI.o: AllAssignedUI.cpp AllAssignedUI.h
		g++ -c AllAssignedUI.cpp `pkg-config gtkmm-3.0 --cflags --libs`

AllPendingUI.o: AllPendingUI.cpp AllPendingUI.h
		g++ -c AllPendingUI.cpp `pkg-config gtkmm-3.0 --cflags --libs`

AllReportsUI.o: AllReportsUI.cpp AllReportsUI.h
		g++ -c AllReportsUI.cpp `pkg-config gtkmm-3.0 --cflags --libs`

Application.o:	Application.cpp Application.h
		g++ -c Application.cpp 

Course.o:	Course.cpp Course.h
		g++ -c Course.cpp 

CourseInfoUI.o:	CourseInfoUI.cpp CourseInfoUI.h
		g++ -c CourseInfoUI.cpp `pkg-config gtkmm-3.0 --cflags --libs`

CourseQueue.o:	CourseQueue.cpp CourseQueue.h
		g++ -c CourseQueue.cpp 

GenInfo.o:	GenInfo.cpp GenInfo.h
		g++ -c GenInfo.cpp 

GradApp.o:	GradApp.cpp GradApp.h
		g++ -c GradApp.cpp 

GradAppFormUI.o: GradAppFormUI.cpp GradAppFormUI.h
		g++ -c GradAppFormUI.cpp `pkg-config gtkmm-3.0 --cflags --libs`

GradAppQueue.o:	GradAppQueue.cpp GradAppQueue.h
		g++ -c GradAppQueue.cpp

GradInfoQueue.o:	GradInfoQueue.cpp GradInfoQueue.h
			g++ -c GradInfoQueue.cpp 

Graduate.o:	Graduate.cpp Graduate.h
		g++ -c Graduate.cpp 

main.o:		main.cpp Types.h
		g++ -c main.cpp `pkg-config gtkmm-3.0 --cflags --libs`

Manager.o:	Manager.cpp Manager.h
		g++ -c Manager.cpp 

OneAssignedUI.o: OneAssignedUI.cpp OneAssignedUI.h
		g++ -c OneAssignedUI.cpp `pkg-config gtkmm-3.0 --cflags --libs`

OnePendingUI.o:	OnePendingUI.cpp OnePendingUI.h
		g++ -c OnePendingUI.cpp `pkg-config gtkmm-3.0 --cflags --libs`

OneReportUI.o:	OneReportUI.cpp OneReportUI.h
		g++ -c OneReportUI.cpp `pkg-config gtkmm-3.0 --cflags --libs`

SelectAppUI.o:	SelectAppUI.cpp SelectAppUI.h
		g++ -c SelectAppUI.cpp `pkg-config gtkmm-3.0 --cflags --libs`

SelectCrsUI.o:	SelectCrsUI.cpp SelectCrsUI.h
		g++ -c SelectCrsUI.cpp `pkg-config gtkmm-3.0 --cflags --libs`

SelectEditUI.o:	SelectEditUI.cpp SelectEditUI.h
		g++ -c SelectEditUI.cpp `pkg-config gtkmm-3.0 --cflags --libs`

SelectEntryUI.o:	SelectEntryUI.cpp SelectEntryUI.h
			g++ -c SelectEntryUI.cpp `pkg-config gtkmm-3.0 --cflags --libs`

StuAppFormUI.o:	StuAppFormUI.cpp StuAppFormUI.h
		g++ -c StuAppFormUI.cpp `pkg-config gtkmm-3.0 --cflags --libs`

StuNumUI.o:	StuNumUI.cpp StuNumUI.h 
		g++ -c StuNumUI.cpp `pkg-config gtkmm-3.0 --cflags --libs`

StuOptionUI.o:	StuOptionUI.cpp StuOptionUI.h 
		g++ -c StuOptionUI.cpp `pkg-config gtkmm-3.0 --cflags --libs`

SubmitAppUI.o:	SubmitAppUI.cpp SubmitAppUI.h
		g++ -c SubmitAppUI.cpp `pkg-config gtkmm-3.0 --cflags --libs`

TACourse.o:	TACourse.cpp TACourse.h
		g++ -c TACourse.cpp 

TACourseInfoUI.o:	TACourseInfoUI.cpp TACourseInfoUI.h
			g++ -c TACourseInfoUI.cpp `pkg-config gtkmm-3.0 --cflags --libs`

TACourseQueue.o:	TACourseQueue.cpp TACourseQueue.h
			g++ -c TACourseQueue.cpp 

TakenCourse.o:	TakenCourse.cpp TakenCourse.h
		g++ -c TakenCourse.cpp 

TakenCourseInfoUI.o:	TakenCourseInfoUI.cpp TakenCourseInfoUI.h
			g++ -c TakenCourseInfoUI.cpp `pkg-config gtkmm-3.0 --cflags --libs`

TakenCourseQueue.o:	TakenCourseQueue.cpp TakenCourseQueue.h
			g++ -c TakenCourseQueue.cpp 

test.o:		test.cpp Types.h
		g++ -c test.cpp 

Tools.o:	Tools.cpp Tools.h
		g++ -c Tools.cpp 

UGradInfoQueue.o:	UGradInfoQueue.cpp UGradInfoQueue.h
			g++ -c UGradInfoQueue.cpp

UGradApp.o:	UGradApp.cpp UGradApp.h
		g++ -c UGradApp.cpp 

UGradAppQueue.o:	UGradAppQueue.cpp UGradAppQueue.h
			g++ -c UGradAppQueue.cpp 

Undergraduate.o:	Undergraduate.cpp Undergraduate.h
			g++ -c Undergraduate.cpp 

WelcomeUI.o:	WelcomeUI.cpp WelcomeUI.h
		g++ -c WelcomeUI.cpp `pkg-config gtkmm-3.0 --cflags --libs`

WorkExp.o:	WorkExp.cpp WorkExp.h
		g++ -c WorkExp.cpp 

WorkExpQueue.o:	WorkExpQueue.cpp WorkExpQueue.h
		g++ -c WorkExpQueue.cpp 

WorkExpUI.o:	WorkExpUI.cpp WorkExpUI.h
		g++ -c WorkExpUI.cpp `pkg-config gtkmm-3.0 --cflags --libs`

clean:
		rm -f *.o cutaes testPgm

package:
		tar -cvf a5.tar $(CPPFILES) Readme $(TXT) *.h Makefile

