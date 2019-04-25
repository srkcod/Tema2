#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

ifstream in("map.in");


struct coord
{
    int x;
    int y;
};

bool fightWinner(int enemy,int agent)
{
    if(enemy==1 && agent==2)
    {
        return false;
    }
    else if(enemy==2 && agent==3)
    {
        return false;
    }
    else if(enemy==3 && agent==1)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool out_of_limit(coord position)
{
    if(position.x>15 || position.x<1 || position.y>15)
    {
        return true;
    }
    else
    {
        return false;
    }
}

class Agent
{
private:
    int hp=1;
    coord agent_position;
    int agent_type;
public:

    coord GetCoord()
    {
        return agent_position;
    }

    void setCoord(coord position)
    {
        agent_position.x = position.x;
        agent_position.y = position.y;
    }
    void setAgentType(int AgentType)
    {
        agent_type = AgentType;
    }
    int getAgentType()
    {
        return agent_type;
    }

};

class Bond: public Agent
{
private:

public:


};
class Wick: public Agent
{
private:


};
class Bourne:public Agent
{
private:

};
class BGround
{
private:
    int n,m;
    coord map_dimension;
    int map_config[100][100];
public:
    coord get_map_coord()
    {
        coord position;
        position.x = n;
        position.y = m;
        return position;
    }
    void load_map()
    {
        in>>n;
        in>>m;
        for(int i=1; i<=n; i++)
        {
            for(int j=1; j<=m; j++)
            {
                in>>map_config[i][j];
            }
        }
    }
    void setPositionValue(int i,coord position)
    {
        map_config[position.x][position.y] = i;
    }

    void print_map()
    {
        for(int i=1; i<=n; i++)
        {
            for(int j=1; j<=m; j++)
            {
                cout<<map_config[i][j]<<" ";
            }
            cout<<'\n';
        }
        cout<<'\n';
    }

    int get_position(coord position)
    {
        return map_config[position.x][position.y];
    }

};

int findAgentInArrayByPosition(vector <Agent> AgentArray,coord position)
{
    for(int i=0; i<AgentArray.size(); i++)
    {
        coord agent_position = AgentArray[i].GetCoord();
        if(agent_position.x == position.x && agent_position.y == position.y)
        {
            return i;
        }
    }
    return -1;
}


void SimulateRound(BGround my_map,vector<Agent> AgentArray,int rounds)
{
    for(int r=1; r<=rounds && AgentArray.size()>1; r++)
    {

        for(int i=0; i<AgentArray.size(); i++)
        {

            coord agent_position = AgentArray[i].GetCoord();

            int xmovement = 0;
            int ymovement = 0;

            if(AgentArray[i].getAgentType()==1)
            {
                ymovement++;
            }
            else if(AgentArray[i].getAgentType()==2)
            {
                ymovement--;
            }
            else
            {
                xmovement++;
            }

            coord enemy_position;

            enemy_position.x = agent_position.x + xmovement;
            enemy_position.y = agent_position.y + ymovement;

            if(my_map.get_position(enemy_position)==4)
            {
                my_map.setPositionValue(0,enemy_position);
                my_map.setPositionValue(0,agent_position);
                AgentArray.erase(AgentArray.begin() + i);
            }
            else if(my_map.get_position(enemy_position)==5)
            {
                AgentArray[i].setAgentType(3);
                AgentArray[i].setCoord(enemy_position);
                my_map.setPositionValue(3,enemy_position);
                my_map.setPositionValue(0,agent_position);
            }
            else
            {

                int enemy_index = findAgentInArrayByPosition(AgentArray,enemy_position);
                if(enemy_index!=-1) /// Am gasit inamic
                {

                    int enemy_type = AgentArray[enemy_index].getAgentType();
                    int agent_type = AgentArray[i].getAgentType();

                    if(fightWinner(enemy_type,agent_type)==true)
                    {

                        my_map.setPositionValue(AgentArray[i].getAgentType(),enemy_position);
                         my_map.setPositionValue(0,agent_position);
                        AgentArray[i].setCoord(enemy_position);
                         AgentArray.erase(AgentArray.begin()+enemy_index);
                    }
                    else
                    {
                        my_map.setPositionValue(0,agent_position);
                        AgentArray.erase(AgentArray.begin()+i);
                    }
                }
                else
                {
                    AgentArray[i].setCoord(enemy_position);
                    my_map.setPositionValue(AgentArray[i].getAgentType(),enemy_position);
                    my_map.setPositionValue(0,agent_position);
                }
            }
            if(out_of_limit(agent_position)==true)
                {
                    AgentArray.erase(AgentArray.begin()+i);
                }
        }
        cout<<r<<'\n';
        my_map.print_map();
    }

}

void Simulate(int rounds,BGround my_map,vector<Agent> AgentArray)
{

    SimulateRound(my_map,AgentArray,rounds);

}

void StartGame()
{
    cout<<"      ,gg,                                                                                                                                           "<<'\n';
    cout<<"     i8""8i                                                                          ,dPYb,                                                          "<<'\n';
    cout<<"     `8,,8'                                                                          IP'`Yb                                                          "<<'\n';
    cout<<"      `88'                                           gg                              I8  8I                                                          "<<'\n';
    cout<<"      dP'8,                                          **                              I8  8*                                                          "<<'\n';
    cout<<"     dP' `8a  gg      gg   ,gggggg,     ggg    gg    gg      ggg    gg     ,gggg,gg  I8 dP          ,gggg,gg    ,gggg,gg   ,ggg,,ggg,,ggg,    ,ggg,  "<<'\n';
    cout<<"    dP'   `Yb I8      8I   dP''''8I    d8'Yb   88bg  88     d8'Yb   88bg  dP'  'Y8I  I8dP          dP'  'Y8I   dP'  'Y8I  ,8' '8P' '8P' '8,  i8' '8i "<<'\n';
    cout<<"_ ,dP'     I8 I8,    ,8I  ,8'    8I   dP  I8   8I    88    dP  I8   8I   i8'    ,8I  I8P          i8'    ,8I  i8'    ,8I  I8   8I   8I   8I  I8, ,8I "<<'\n';
    cout<<"'888,,____,dP,d8b,  ,d8b,,dP     Y8,,dP   I8, ,8I  _,88,_,dP   I8, ,8I  ,d8,   ,d8b,,d8b,_       ,d8,   ,d8I ,d8,   ,d8b,,dP   8I   8I   Yb, `YbadP' "<<'\n';
    cout<<"a8P'Y88888P' 8P''Y88P'`Y88P      `Y88'     'Y8P'   8P''Y88'     'Y8P'   P'Y8888P'`Y88P''Y88      P'Y8888P'888P'Y8888P'`Y88P'   8I   8I   `Y8888P'Y888"<<'\n';
    cout<<"                                                                                                        ,d8I'                                        "<<'\n';
    cout<<"                                                                                                      ,dP'8I                                         "<<'\n';
    cout<<"                                                                                                     ,8'  8I                                         "<<'\n';
    cout<<"                                                                                                     I8   8I                                         "<<'\n';
    cout<<"                                                                                                     `8, ,8I                                         "<<'\n';
    cout<<"                                                                                                      `Y8P'                                          "<<'\n';

}

vector<Agent> LoadAgents(BGround my_map)
{
    vector <Agent> AgentArray;
    ///Luam agentii de pe configuratie

    coord map_dimensions = my_map.get_map_coord();

    for(int i=1; i<=map_dimensions.x; i++)
    {
        for(int j=1; j<=map_dimensions.y; j++)
        {
            coord position;
            position.x = i;
            position.y = j;
            if(my_map.get_position(position)==1 || my_map.get_position(position)==2 || my_map.get_position(position)==3)
            {
                Agent new_agent;
                coord position;
                position.x = i;
                position.y = j;
                new_agent.setCoord(position);
                new_agent.setAgentType(my_map.get_position(position));

                AgentArray.push_back(new_agent);
            }
        }
    }
    cout<<"Loading Agents..."<<'\n';
    return AgentArray;
}

int main()
{
    vector <Agent> AgentArray;
    int rounds;

    /// StartGame
    StartGame();

    ///Load Map
    BGround my_map;
    my_map.load_map();

    ///Load Agents
    AgentArray = LoadAgents(my_map);

    /// Round Selector
    cout<<"Numar runde: ";
    cin>>rounds;

    ///Simulare
    Simulate(rounds,my_map,AgentArray);

    return 0;
}
