#include <iostream>
#include <string>

#include "Queue.h"
#include "Stack.h"

static bool IsValidCmdChar(char c)
{
    return c == 'A' || c == 'B' || c == 'C' || c == 'D' || c == 'E';
}

static void Execute(char cmd)
{
    std::cout << "[EXEC] " << cmd << "\n";
}

static void UndoAction(char cmd)
{
    std::cout << "[UNDO] " << cmd << "\n";
}

static void PrintStack(const char* title, const Stack& st)
{
    std::cout << "== " << title << " (top -> bottom) ==\n";
    if (st.IsEmpty())
    {
        std::cout << "(empty)\n";
        return;
    }

    for (int i = 0; i < st.Size(); ++i)
    {
        char c = st.GetAt(i);
        std::cout << c << (i == st.Size() - 1 ? "\n" : " ");
    }
}

int main()
{
    Queue inputQ(64);
    Stack undoSt(128);
    Stack redoSt(128);

    std::cout << "  A/B/C/D/E : enqueue input\n";
    std::cout << "  process\n";
    std::cout << "  undo\n";
    std::cout << "  redo\n";
    std::cout << "  show\n";
    std::cout << "  quit\n\n";

    while (true)
    {
        std::cout << "> ";
        std::string cmd;
        std::cin >> cmd;

        if (cmd == "quit")
            break;

        // A~E 입력.
        if (cmd.size() == 1 && IsValidCmdChar(cmd[0]))
        {
            if (!inputQ.Push(cmd[0]))
                std::cout << "InputQueue full!\n";
            else
                std::cout << "Enqueued: " << cmd[0] << "\n";
            continue;
        }

        // queue에 쌓인 것 실행 + undo 기록 + redo 비우기.
        if (cmd == "process")
        {
            char c;
            bool any = false;

            while (inputQ.Pop(c))
            {
                any = true;
                Execute(c);

                // 새 입력 실행이 발생했으므로 redo 스택 비우기.
                redoSt.Clear();

                if (!undoSt.Push(c))
                    std::cout << "UndoStack full!\n";
            }

            if (!any)
                std::cout << "(queue empty)\n";

            continue;
        }

        if (cmd == "undo")
        {
            char c;
            if (!undoSt.Pop(c))
            {
                std::cout << "(undo empty)\n";
                continue;
            }

            UndoAction(c);

            if (!redoSt.Push(c))
                std::cout << "RedoStack full!\n";

            continue;
        }

        if (cmd == "redo")
        {
            char c;
            if (!redoSt.Pop(c))
            {
                std::cout << "(redo empty)\n";
                continue;
            }

            Execute(c);

            if (!undoSt.Push(c))
                std::cout << "UndoStack full!\n";

            continue;
        }

        if (cmd == "show")
        {
            PrintStack("UNDO", undoSt);
            PrintStack("REDO", redoSt);
            continue;
        }

        std::cout << "Unknown command\n";
    }

    return 0;
}