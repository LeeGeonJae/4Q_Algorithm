#include <functional> //std::function
#include <iostream>
#include <conio.h>
#include <map>
#include <thread>
#include <concurrent_queue.h>
using namespace Concurrency;

using namespace std;

// �� �ֹ��ߴ°�.
enum class CMD_TYPE : unsigned short
{
	NONE = 0,
	EĿ�� = 1,
	E������ġ,
	E������
};

// �ֹ��� Ÿ��
class CmdMsg
{
public:
	CMD_TYPE cmdType;

protected:
	CmdMsg() { cmdType = CMD_TYPE::NONE; }
};

class CmdĿ�� : public CmdMsg
{
public:
	CmdĿ��(const char* type)
	{
		cmdType = CMD_TYPE::EĿ��;
		m_type = type;
	}

	string m_type;

private:
	CmdĿ��() = delete;
};

class Cmd������ġ : public CmdMsg
{
public:
	Cmd������ġ(int type)
	{
		cmdType = CMD_TYPE::E������ġ;
		m_type = type;
	}

	int m_type;

private:
	Cmd������ġ() = delete;
};

class Cmd������ : public CmdMsg
{
public:
	Cmd������(int param1, int param2)
	{
		cmdType = CMD_TYPE::E������;
		m_param1 = param1;
		m_param2 = param2;
	}

	int m_param1;
	int m_param2;

private:
	Cmd������() = delete;
};


// ó�� = �Լ�
void MakeĿ��(string param)
{
	cout << param << " Ŀ�� ��Ű�� ��?" << endl;
}

void Make������ġ(int nParam1)
{
	if (nParam1 < 0 || nParam1 >= 2)
	{
		cout << "���Ⱦ�" << endl;
		return;
	}

	string ������ġ����[2] = { "�ܻ�����ġ", "ġŲ������ġ" };

	cout << ������ġ����[nParam1] << "��Ű�� ��?" << endl;
}

void Make������(int nParam1, int nParam2)
{
	if (nParam1 < 0 || nParam1 >= 2 || nParam2 < 0 || nParam2 >= 2)
	{
		cout << "���Ⱦ�" << endl;
		return;
	}

	string ����������[2] = { "�ſ����", "����������" };
	string ������[2] = { "����", "Ư��" };

	cout << ����������[nParam1] << " " << ������[nParam2] << " ��Ű�� ��?" << endl;

}

class CmdDiapatcher
{
public:
	void InitCommand()
	{
		m_cmdMap.emplace(CMD_TYPE::EĿ��, [](CmdMsg* cmdMsg) {
			CmdĿ��* pCmd = reinterpret_cast<CmdĿ��*>(cmdMsg);
			MakeĿ��(pCmd->m_type);
			});

		m_cmdMap.emplace(CMD_TYPE::E������ġ, [](CmdMsg* cmdMsg) {
			Cmd������ġ* pCmd = reinterpret_cast<Cmd������ġ*>(cmdMsg);
			Make������ġ(pCmd->m_type);
			});

		m_cmdMap.emplace(CMD_TYPE::E������, [](CmdMsg* cmdMsg) {
			Cmd������* pCmd = reinterpret_cast<Cmd������*>(cmdMsg);
			Make������(pCmd->m_param1, pCmd->m_param2);
			});
	}

	void DispatchCommand(CmdMsg* cmdMsg)
	{
		auto cmdFun = FindCommand(cmdMsg);
		cmdFun(cmdMsg);
	}

	//void FindCommand(CmdMsg* cmdMsg)
	std::function<void(CmdMsg*)> FindCommand(CmdMsg* cmdMsg)
	{
		CmdMsg* cmd = reinterpret_cast<CmdMsg*>(cmdMsg);

		auto it = m_cmdMap.find(cmd->cmdType);
		if (it == m_cmdMap.end()) std::terminate();
		return it->second;
	}

private:
	std::map<CMD_TYPE, std::function<void(CmdMsg*)> > m_cmdMap;
};

int main()
{
	cout << "hardware_concurrency : " << std::thread::hardware_concurrency() << endl;

	// �Լ� ��ü Ȱ��
	CmdDiapatcher _cmdDispatcher;
	_cmdDispatcher.InitCommand();


	concurrent_queue<shared_ptr<CmdMsg>> msgQueue;

	auto workFun = ([&_cmdDispatcher, &msgQueue]
		{
			int count = 0;
			while (count < 10)
			{
				shared_ptr<CmdMsg> Cmd;
				if (msgQueue.try_pop(Cmd))
				{
					_cmdDispatcher.DispatchCommand(Cmd.get());
					++count;

					// ���⿡ current thread id�� ����� ������.
				}
			}

			cout << "��� ��!" << endl;

		} // �ٸ� ������!!
	);

	// thread �� �� ���� ���� (worker �Լ�) -> (worker ��ü)
	std::thread workerThread(workFun);

	// ���� ���� ������
	int KeyInfo;

	do
	{
		KeyInfo = _getch();

		if (tolower(KeyInfo) == '1')
		{
			shared_ptr<CmdMsg> cmdMsg(new CmdĿ��("�ƾ�"));
			msgQueue.push(cmdMsg);
		}
		else if (tolower(KeyInfo) == '2')
		{
			shared_ptr<CmdMsg> cmdMsg(new Cmd������ġ(1));
			msgQueue.push(cmdMsg);
		}
		else if (tolower(KeyInfo) == '3')
		{
			shared_ptr<CmdMsg> cmdMsg(new Cmd������(1, 1));
			msgQueue.push(cmdMsg);
		}

	} while (tolower(KeyInfo) != 'q');

	workerThread.join();

	system("pause");
}