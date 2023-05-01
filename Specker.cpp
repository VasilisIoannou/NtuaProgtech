    #include<iostream>
    #include<stdexcept>

    using namespace std;

    class Move{
    public:
        // Take sc coins from heap sh and put tc coins to heap th.
        Move(int sh,int sc, int th, int tc);

        int getSource() const;
        int getSourceCoins() const;
        int getTarget() const;
        int getTargetCoins() const;

        friend ostream & operator << (ostream &out,const Move &move){
            out<<"takes "<<move.sCoins<<" coins from heap "<<move.sHeap<<" and puts ";
            if(move.tCoins>0)
                out<<move.tCoins<<" coins to heap "<<move.tHeap;
            else
                out<<"nothing";

            return out;
        }

    private:
        int sHeap,sCoins,tHeap,tCoins;
    };

    Move::Move(int sh,int sc, int th, int tc){
        sHeap = sh;
        sCoins = sc;
        tCoins = tc;
        tHeap = th;
    }

    int Move::getSource() const{
        return sHeap;
    }
    int Move::getSourceCoins() const{
        return sCoins;
    }
    int Move::getTarget() const{
        return tHeap;
    }
    int Move::getTargetCoins() const{
        return tCoins;
    }

    class State{
    public:
            State(int h,const int c[],int n);
            ~State();

            void next(const Move &move) ;
            bool winning() const;

            int getHeaps() const;
            int getCoins(int h)const ;

            int getPlayers() const;
            int getPlaying() const;

            friend ostream & operator <<(ostream& out,const State &state){
                for(int i=0;i<state.Heaps-1;i++)
                    out<<state.Coins[i]<<", ";
                out<<state.Coins[state.Heaps-1];
                out<<" with "<<state.CurrentPlayer<<"/"<<state.Players<<" playing next";

                return out;
            }
    private:
        int Heaps,Players,CurrentPlayer;
        int *Coins;
    };

    State::State(int h,const int c[],int n){
        Heaps = h;
        Players = n;
        CurrentPlayer=0;
        Coins = new int[h];
        for(int i=0;i<h;i++)
            Coins[i] = c[i];
    }
    State::~State(){
        delete[] Coins;
    }
    void State::next(const Move &move) {
        int CurrentHeap = move.getSource();

        if(CurrentHeap<0 || CurrentHeap >= Heaps) throw logic_error("invalid heap");

        int HeapCoins = move.getSourceCoins();
        int TargetHeap = move.getTarget();
        int TargetCoins = move.getTargetCoins();

        Coins[CurrentHeap]-= HeapCoins;

        if(Coins[CurrentHeap]<0) throw logic_error("invalid coins");
        if(TargetCoins>=HeapCoins) throw logic_error("invalid coins");

        Coins[TargetHeap] += TargetCoins;

        if(Players==1) throw logic_error("invalid Players");

        if(CurrentPlayer < Players-1)
            CurrentPlayer++;
        else CurrentPlayer=0;
    }
    bool State::winning() const{
        bool Win = true;
        for(int i=0;i<Heaps;i++)
            if(Coins[i]>0) Win = false;
        return Win;
    }

    int State::getHeaps() const{
        return Heaps;
    }

    int State::getCoins(int h)const {
        if(h<0 || h >=Heaps) throw logic_error("invalid heap");
        return Coins[h];
    }

    int State::getPlayers() const{
        return Players;
    }

    int State::getPlaying() const{
        return CurrentPlayer;
    }
class Player{
public:
    Player(const string &n){ Name = n; }
    virtual ~Player(){ }
    virtual const string& getType() const =0;
    virtual Move play(const State &s)=0;

    friend ostream& operator << (ostream& out,const Player& player){
        out<< player.getType() << " player " << player.Name;
        return out;
    }

    string getName(){
        return Name;
    }
protected:
    string Name;
};

class GreedyPlayer: public Player{
public:
    GreedyPlayer(const string &n) : Player(n){ Name = n; }
    ~GreedyPlayer() override { delete[] Coins; }
    const string& getType() const override{
        const string &s = Type;
        return s;
    }
    Move play(const State &s) override{
        int Heaps = s.getHeaps();
        Coins = new int[Heaps];
        for(int i=0;i<Heaps;i++)
            Coins[i] = s.getCoins(i);

        int Max = Coins[0],ChosenHeap;

        for(int i=1;i<Heaps;i++)
        if(Coins[i]>Max){
            ChosenHeap=i;
            Max = Coins[i];
        }

        Move GreedyMove(ChosenHeap,Max,0,0);
        return GreedyMove;
    }
private:
    string Type = "Greedy";
    int *Coins;
};

class SpartanPlayer: public Player{
public:
    SpartanPlayer(const string &n) : Player(n){ Name = n; }
    ~SpartanPlayer() override { delete[] Coins; }
    const string& getType()const override {
        const string &s = Type;
        return s;
    }
    Move play(const State &s) override{
        int Heaps = s.getHeaps();
        Coins = new int[Heaps];
        for(int i=0;i<Heaps;i++)
            Coins[i] = s.getCoins(i);

        int Max = Coins[0],ChosenHeap;

        for(int i=1;i<Heaps;i++)
        if(Coins[i]>Max){
            ChosenHeap=i;
            Max = Coins[i];
        }

        Move SpartanMove(ChosenHeap,1,0,0);
        return SpartanMove;
    }
private:
    string Type = "Spartan";
    int *Coins;
};

class SneakyPlayer: public Player{
public:
    SneakyPlayer(const string &n) : Player(n){ Name = n; }
    ~SneakyPlayer() override { delete[] Coins; }
    const string& getType() const override{
        const string &s = Type;
        return s;
    }
    Move play(const State &s) override{
        int Heaps = s.getHeaps();
        Coins = new int[Heaps];
        for(int i=0;i<Heaps;i++)
            Coins[i] = s.getCoins(i);

        int j=0;
        while(Coins[j]==0) j++;
        int Min = Coins[j],ChosenHeap=j;

        for(int i=1;i<Heaps;i++)
        if(Coins[i] < Min && Coins[i]>0){
            ChosenHeap=i;
            Min = Coins[i];
        }

        Move SneakyMove(ChosenHeap,Min,0,0);
        return SneakyMove;
    }
private:
    string Type = "Sneaky";
    int *Coins;
};

class RighteousPlayer: public Player{
public:
    RighteousPlayer(const string &n) : Player(n){ Name = n; }
    ~RighteousPlayer() override { delete[] Coins; }
    const string& getType() const override{
        const string &s = Type;
        return s;
    }
    Move play(const State &s) override{
        int Heaps = s.getHeaps();
        Coins = new int[Heaps];
        for(int i=0;i<Heaps;i++)
            Coins[i] = s.getCoins(i);

        int Max = Coins[0],ChosenHeap;

        for(int i=1;i<Heaps;i++)
        if(Coins[i]>Max){
            ChosenHeap=i;
            Max = Coins[i];
        }

        int Min = Coins[0],GiveHeap=0;

        for(int i=1;i<Heaps;i++)
        if(Coins[i] < Min){
            GiveHeap=i;
            Min = Coins[i];
        }

        int TargetCoins;
        if(Max%2==0) TargetCoins=Max/2;
        else TargetCoins=Max/2+1;

        Move RighteousMove(ChosenHeap,TargetCoins,GiveHeap,TargetCoins-1);
        return RighteousMove;
    }
private:
    string Type = "Righteous";
    int *Coins;
};

class Game {
public:
    Game(int heaps, int players);
    ~Game();

    void addHeap(int coins) ;
    void addPlayer(Player *player) ;
    void play(ostream &out) ;

    int getPlayers() const;
    const Player* getPlayer(int p) const ;

private:
    int GameHeaps,GamePlayers,CurrentPlayer;
    int *HeapList;
    Player **PlayerList;
};

Game::Game(int heaps, int players){
    CurrentPlayer = 0;
    GameHeaps = heaps;

    HeapList = new int[heaps];
    for(int i=0;i<heaps;i++)
        HeapList[i]=-1;

    GamePlayers = players;

    PlayerList = new Player*[GamePlayers];
    for(int i=0;i<GamePlayers;i++)
       PlayerList[i]=nullptr;
}

Game::~Game(){
    delete[] HeapList;
    delete[] PlayerList;
}

void Game::addHeap(int coins) {
    int i=0;

    while(HeapList[i] != -1 && i < GameHeaps) i++;

    HeapList[i] = coins;
}
void Game::addPlayer(Player *player) {
    int i=0;

    while(PlayerList[i] != nullptr && i < GamePlayers) i++;

    PlayerList[i] = player;
}

int Game::getPlayers() const{
    return GamePlayers;
}

const Player* Game::getPlayer(int p) const {
    return PlayerList[p];
}

 void Game::play(ostream &out) {
    State CurrentState(GameHeaps,HeapList,GamePlayers);
    while(!CurrentState.winning()){
        out<<"State: ";
        for(int i=0;i<GameHeaps-1;i++)
            out<<HeapList[i] << ", ";
        out<<HeapList[GameHeaps-1] << " with " << CurrentPlayer << "/" << GamePlayers << " playing next"<<endl;

        Move NextMove = PlayerList[CurrentPlayer]->play(CurrentState);
        CurrentState.next(NextMove);

        for(int i=0;i<GameHeaps;i++)
            HeapList[i]=CurrentState.getCoins(i);

        int SourceHeap = NextMove.getSource();
        int SourceCoins = NextMove.getSourceCoins();
        int TargetHeap = NextMove.getTarget();
        int TargetCoins = NextMove.getTargetCoins();
        // << PlayerList[CurrentPlayer]->name
        out<<*PlayerList[CurrentPlayer] << " takes " << SourceCoins << " coins from heap " << SourceHeap << " and puts ";
        if(TargetCoins==0) out<<"nothing "<<endl;
        else out<<TargetCoins << "coins to heap" << TargetHeap;

        if(CurrentPlayer<GamePlayers-1) CurrentPlayer++;
        else CurrentPlayer=0;
    }
 }
