OBJS:=main.o game.o MainWindow.o ChessBoard.o
CPP:=g++ -std=c++11
Q:=@

renju: $(OBJS)
	$(Q)$(CPP) $^ -o $@
	$(Q)echo "Done."

%.o: %.cpp
	$(Q)$(CPP) -c $^ -o $@

clean:
	$(Q)rm -f *.o  *.gch
	$(Q)echo "Cleaned."

#makefile语法解释：$(Q)表示取变量Q的值，@表示目文件名字，^表示所有依赖文件名字, @ ^都是预定义变量, OBJS CPP Q都是自定义变量。

