OBJS = CLStatus.o CLThread.o CLExecutive.o CLExecutiveFunctionProvider.o CLExecutiveFunctionForMsgLoop.o CLMutex.o CLCriticalSection.o CLConditionVariable.o CLEvent.o CLMessage.o CLMessageQueueBySTLList.o CLMessageLoopManager.o CLMsgLoopManagerForQueueBySTLList.o CLExecutiveCommunication.o CLThreadCommunicationForQueueBySTLList.o CLExecutiveNameServer.o CLThreadForMsgLoop.o CLNonThreadForMsgLoop.o CLMainMsgProcessor.o CLControlMsgProcessor.o CLCalculateMsgProcessor.o

libexe.a: ${OBJS} 
	ar -rc libexe.a ${OBJS}
	rm ${OBJS}

CLStatus.o : ./src/CLStatus.cpp
	g++ -c ./src/CLStatus.cpp -I./inc -g

CLExecutive.o : ./src/CLExecutive.cpp
	g++ -c ./src/CLExecutive.cpp -I./inc -g -lpthread

CLExecutiveFunctionProvider.o : ./src/CLExecutiveFunctionProvider.cpp
	g++ -c ./src/CLExecutiveFunctionProvider.cpp -I./inc -g -lpthread

CLExecutiveFunctionForMsgLoop.o : ./src/CLExecutiveFunctionForMsgLoop.cpp
	g++ -c ./src/CLExecutiveFunctionForMsgLoop.cpp -I./inc -g -lpthread

CLThread.o : ./src/CLThread.cpp
	g++ -c ./src/CLThread.cpp -I./inc -g -lpthread

CLMutex.o : ./src/CLMutex.cpp
	g++ -c ./src/CLMutex.cpp -I./inc -g -lpthread

CLCriticalSection.o : ./src/CLCriticalSection.cpp
	g++ -c ./src/CLCriticalSection.cpp -I./inc -g -lpthread

CLConditionVariable.o : ./src/CLConditionVariable.cpp
	g++ -c ./src/CLConditionVariable.cpp -I./inc -g -lpthread

CLEvent.o : ./src/CLEvent.cpp
	g++ -c ./src/CLEvent.cpp -I./inc -g -lpthread

CLMessage.o : ./src/CLMessage.cpp
	g++ -c ./src/CLMessage.cpp -I./inc -g -lpthread

CLMessageQueueBySTLList.o : ./src/CLMessageQueueBySTLList.cpp
	g++ -c ./src/CLMessageQueueBySTLList.cpp -I./inc -g -lpthread

CLMessageLoopManager.o : ./src/CLMessageLoopManager.cpp
	g++ -c ./src/CLMessageLoopManager.cpp -I./inc -g -lpthread

CLMsgLoopManagerForQueueBySTLList.o : ./src/CLMsgLoopManagerForQueueBySTLList.cpp
	g++ -c ./src/CLMsgLoopManagerForQueueBySTLList.cpp -I./inc -g -lpthread

CLExecutiveCommunication.o : ./src/CLExecutiveCommunication.cpp
	g++ -c ./src/CLExecutiveCommunication.cpp -I./inc -g -lpthread

CLThreadCommunicationForQueueBySTLList.o : ./src/CLThreadCommunicationForQueueBySTLList.cpp
	g++ -c ./src/CLThreadCommunicationForQueueBySTLList.cpp -I./inc -g -lpthread

CLExecutiveNameServer.o : ./src/CLExecutiveNameServer.cpp
	g++ -c ./src/CLExecutiveNameServer.cpp -I./inc -g -lpthread

CLThreadForMsgLoop.o : ./src/CLThreadForMsgLoop.cpp
	g++ -c ./src/CLThreadForMsgLoop.cpp -I./inc -g -lpthread

CLNonThreadForMsgLoop.o : ./src/CLNonThreadForMsgLoop.cpp
	g++ -c ./src/CLNonThreadForMsgLoop.cpp -I./inc -g -lpthread

CLMainMsgProcessor.o : ./src/CLMainMsgProcessor.cpp
	g++ -c ./src/CLMainMsgProcessor.cpp -I./inc -g -lpthread

CLControlMsgProcessor.o : ./src/CLControlMsgProcessor.cpp
	g++ -c ./src/CLControlMsgProcessor.cpp -I./inc -g -lpthread

CLCalculateMsgProcessor.o : ./src/CLCalculateMsgProcessor.cpp
	g++ -c ./src/CLCalculateMsgProcessor.cpp -I./inc -g -lpthread

main.o: main.cpp 
	g++ -c main.cpp -I./inc -g -lpthread

main: libexe.a main.o
	g++ -o main main.o libexe.a -g -lpthread
	rm main.o
clean:
	rm -f main libexe.a *.o 

#reference the target object will directly execute the command that target object repersents
