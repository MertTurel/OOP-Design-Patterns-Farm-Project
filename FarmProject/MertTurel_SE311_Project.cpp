///Mert TUREL SE311_2016 Project
///LIVESTOCK FARM SOLUTION

#include<iostream>
#include<string>
#include<vector>

using namespace std;

class Visitor;
class Beef_Cattle;
class Milk_Cattle;
//This Is The Pre-Definations For Concrete Observers
class ZigbeeTracker;
class BluetoothTracker;

//AbstractElement For Visitors
class LiveStock{
public:
    virtual ~LiveStock(){};
    //Abstract Accept Method For Visitors
	virtual void Accept(Visitor* visitor) {};
protected:
	LiveStock(){};
};

//My Abstract Visitor Class
class Visitor{
public:
    virtual ~Visitor(){};
    virtual void visit(Beef_Cattle *beef) = 0;
    virtual void visit(Milk_Cattle *milk) = 0;
    Visitor(){};
};

//AbstractSubject and also concrete element for visitor pattern
class Animal : public LiveStock{
public:

    virtual ~Animal(){}
    //Parametrized Constructor
    Animal(string name , bool vacc , bool tag) : _name(name) , is_vaccated(vacc) , has_ear_tag(tag) {};
    //Default Constructor
    Animal(){}

    virtual void attachZigbeeTracker(ZigbeeTracker *trc , Animal *anim);
    virtual void detachZigbeeTracker(ZigbeeTracker *trc , Animal *anim);

    virtual void attachBluetoothTracker(BluetoothTracker *trc , Animal *anim);
    virtual void detachBluetoothTracker(BluetoothTracker *trc , Animal *anim);

    virtual void notify();
    // We don't track Z location so we assuming cattles can't fly :D !!
    virtual void setLocation(double locX , double locY) {};
    virtual double getLocation_x(){return 0;};
    virtual double getLocation_y(){return 0;};

    //Setter and getters for set health attributes by visitors
    void setVaccination(bool vacc){
        is_vaccated = vacc;
    }

    bool getVaccInfo(){
        return is_vaccated;
    }

    void setEarTag(bool tag){
        has_ear_tag = tag;
    }

    bool getTagInfo(){
        return has_ear_tag;
    }

    string getName(){return _name;}

private:
    Animal *anml;
    bool is_vaccated;
    bool has_ear_tag;
    string _name;
    vector<BluetoothTracker*> BluetoothTrackers;
    vector<ZigbeeTracker*> ZigbeeTrackers;

};

//ConcreteSubject
class Beef_Cattle : public Animal{
public:

    Beef_Cattle(string name , double loc_x , double loc_y) : Animal(name , false , false) , location_x(loc_x) , location_y(loc_y) {}

    //Overriding Accept Method
    void Accept(Visitor* vstr) {vstr->visit(this);}

    double getLocation_x(){
        return location_x;
    }

    double getLocation_y(){
        return location_y;
    }

    void setLocation(double x , double y){
        location_x = x;
        location_y = y;
        //We assuming the farm boundaries x = 250m  y = 150m
        //If cattle exits the farm boundaries farmer gets notified.
        if(location_x > 125.0 | location_y > 75.0 | location_x < -125.0 | location_y < -75.0){
            notify();
        }
    }

private:

    double location_x;
    double location_y;
};

//ConcreteSubject

class Milk_Cattle : public Animal{
public:

    Milk_Cattle(string name , double loc_x , double loc_y) : Animal(name , false , false) , location_x(loc_x) , location_y(loc_y) {}

    //Overriding Accept Method
    void Accept(Visitor* vstr) {vstr->visit(this);}

    double getLocation_x(){
        return location_x;
    }

    double getLocation_y(){
        return location_y;
    }

    void setLocation(double x , double y){
        location_x = x;
        location_y = y;
        //We assuming the farm boundaries x = 250m  y = 150m
        //If cattle exits the farm boundaries farmer gets notified.
        if(location_x > 125.0 | location_y > 75.0 | location_x < -125.0 | location_y < -75.0){
            notify();
        }
    }

private:

    double location_x;
    double location_y;
};

//This is a high level interface to let visitors to be accepted and visit elements in a composite structure(Object Structure)
class Cattles{
private:
    vector<Animal*> catt;
public:
    //Adding Cattles in Visitor List(Vector)
    void Add(Animal *_anml){
        catt.push_back(_anml);
    }
    //Removing from list(Vector)
    void Remove(Animal *_anml){
        for(int i = 0 ; i< catt.size() ; i++){
            if(catt[i]->getName() == _anml->getName()){
                catt.erase(catt.begin()+i);
                }
            }
        }
    //Accept visitors
    void Accept(Visitor *vstr){
        for(int i = 0 ; i< catt.size() ; i++){
            catt[i] -> Accept(vstr);
        }
    }

};

//Concrete Visitors (Veterinary and Ministry_Inspector)
//Concrete Visitor 1
class Veterinary : public Visitor{
public:
    //Veterinary Visits Beef Cattles in Farm
    void visit(Beef_Cattle *beef){
        if(beef -> getVaccInfo() == false){
            cout<<"Beef Cattle "<<beef->getName()<<" doesn't have vaccination , vacc value = "<< beef->getVaccInfo() << " , now vaccination in progress by a veterinary !!!" <<endl;
            beef->setVaccination(true);
            cout<< "Beef Cattle " << beef->getName() << " now have vaccination and new vacc value = "<< beef->getVaccInfo()<<endl;
        }
        else if(beef -> getVaccInfo() == true){
            cout<<"Beef Cattle "<<beef->getName() << " already have vaccination !!"<<endl;
        }
    };

    //Veterinary Visits Milk Catlles in Farm
    void visit(Milk_Cattle *milk){
         if(milk -> getVaccInfo() == false){
            cout<<"Milk Cattle "<<milk->getName()<<" doesn't have vaccination , vacc value = "<< milk->getVaccInfo() << " , now vaccination in progress by a veterinary !!!" <<endl;
            milk->setVaccination(true);
            cout<< "Milk Cattle " << milk->getName() << " now have vaccination and new vacc value = "<< milk->getVaccInfo()<<endl;
        }
        else if(milk -> getVaccInfo() == true){
            cout<<"Milk Cattle "<<milk->getName() << " already have vaccination !!"<<endl;
        }
    };
};

//Concrete Visitor 2
class Ministry_Inspector : public Visitor{
public:
    //Inpector Visits Beef Cattles in Farm
    void visit(Beef_Cattle *beef){
         if(beef -> getTagInfo() == false){
            cout<<"Beef Cattle "<<beef->getName()<<" doesn't have ear tag , tag value = "<< beef->getTagInfo() << " , now tagging cattles ear in progress by an inspector !!!" <<endl;
            beef->setEarTag(true);
            cout<< "Beef Cattle " << beef->getName() << " now have an ear tag and new tag value = "<< beef->getTagInfo()<<endl;
        }
        else if(beef -> getTagInfo() == true){
            cout<<"Beef Cattle "<<beef->getName() << " have ear tag !!"<<endl;
        }
    };

    //Inspector Visits Milk Cattles in Farm
    void visit(Milk_Cattle *milk){
        if(milk -> getTagInfo() == false){
            cout<<"Milk Cattle "<<milk->getName()<<" doesn't have ear tag , tag value = "<< milk->getTagInfo() << " , now tagging cattles ear in progress by an inspector !!!" <<endl;
            milk->setEarTag(true);
            cout<< "Milk Cattle " << milk->getName() << " now have an ear tag and new tag value = "<< milk->getTagInfo()<<endl;
        }
        else if(milk -> getTagInfo() == true){
            cout<<"Milk Cattle "<<milk->getName() << " have ear tag !!"<<endl;
        }
    };
};

//Abstract Product Class 1
class Protein{
public:
    virtual void prepareFood(double food_weight) = 0;
    virtual void eatFood(double eat_weight) = 0;
};

//Concrete Product 1 For Milk Cattle Protein
class Soybean : public Protein{
private:
    double food_weight_in_plate;
    Animal *_anml;
public:
    Soybean(Animal *anml) : _anml(anml) , food_weight_in_plate(0.0) {
        cout<<"Creating Soybean (Protein For Milk Cattle)!!"<<endl;
    };
    void prepareFood(double food_weight){
        food_weight_in_plate += food_weight;
        cout<<"There is "<<food_weight<<" kg soybean (Protein) in milk cattle "<<_anml->getName()<<" 's plate"<<endl;
    }
    void eatFood(double eat_weight){
        if(food_weight_in_plate >= eat_weight){
            food_weight_in_plate -= eat_weight;
            cout<<eat_weight<<" kg soybean (Protein) eaten by milk cattle "<<_anml->getName()<<endl;
            cout<<"There is "<<food_weight_in_plate<< " kg soybean left in plate "<<endl;
            if(eat_weight <= 1.0){
                cout<<"Cattle eat too few it may be sick!!"<<endl;
            }
        }
        else{
            cout<<"There is not enough food in plate please prepare some more food "<<endl;
        }
    }
};

//Concrete Product 1 For Beef Cattle Protein
class Canola : public Protein{
private:
    double food_weight_in_plate;
    Animal *_anml;
public:
    Canola(Animal *anml) : _anml(anml) , food_weight_in_plate(0.0) {
        cout<<"Creating Canola (Protein For Beef Cattle)!!"<<endl;
    }
    void prepareFood(double food_weight){
        food_weight_in_plate += food_weight;
        cout<<"There is "<<food_weight<<" kg canola (Protein) in beef cattle "<<_anml->getName()<<" 's plate"<< endl;
    }
    void eatFood(double eat_weight){
        if(food_weight_in_plate >= eat_weight){
            food_weight_in_plate -= eat_weight;
            cout<<eat_weight<<" kg canola (Protein) eaten by beef cattle "<<_anml->getName()<<endl;
            cout<<"There is "<<food_weight_in_plate<< " kg canola left in plate "<<endl;
            if(eat_weight <= 1.0){
                cout<<"Cattle eat too few it may be sick!!"<<endl;
            }
        }
        else{
            cout<<"There is not enough food in plate please prepare some more food "<<endl;
        }
    }
};

//Abstract Product Class 2
class Carbonhydrate{
public:
    virtual void prepareFood(double food_weight) = 0;
    virtual void eatFood(double eat_weight) = 0;
};

//Concrete Product 2 For Milk Cattle Carbonhydrate
class Corn : public Carbonhydrate{
private:
    double food_weight_in_plate;
    Animal *_anml;
public:
    Corn(Animal * anml) : _anml(anml) , food_weight_in_plate(0.0) {
        cout<<"Creating Corn (Carbonhydrate For Milk Cattle)!!"<<endl;
    }
    void prepareFood(double food_weight){
        food_weight_in_plate += food_weight;
        cout<<"There is "<<food_weight<<" kg corn (Carbonhydrate) in milk cattle "<<_anml->getName()<<" 's plate"<< endl;
    }
    void eatFood(double eat_weight){
        if(food_weight_in_plate >= eat_weight){
            food_weight_in_plate -= eat_weight;
            cout<<eat_weight<<" kg corn (Carbonhydrate) eaten by milk cattle "<<_anml->getName()<<endl;
            cout<<"There is "<<food_weight_in_plate<< " kg corn left in plate "<<endl;
            if(eat_weight <= 1.0){
                cout<<"Cattle eat too few it may be sick!!"<<endl;
            }
        }
        else{
            cout<<"There is not enough food in plate please prepare some more food "<<endl;
        }
    }
};

//Concrete Product 2 For Beef Cattle Carbonhydrate
class Wheat : public Carbonhydrate{
private:
    double food_weight_in_plate;
    Animal *_anml;
public:
    Wheat(Animal * anml) : _anml(anml) , food_weight_in_plate(0.0) {
        cout<<"Creating Wheat (Carbonhydrate For Beef Cattle)!!"<<endl;
    }
    void prepareFood(double food_weight){
        food_weight_in_plate += food_weight;
        cout<<"There is "<<food_weight<<" kg wheat (Carbonhydrate) in beef cattle "<<_anml->getName()<<" 's plate"<< endl;
    }
    void eatFood(double eat_weight){
        if(food_weight_in_plate >= eat_weight){
            food_weight_in_plate -= eat_weight;
            cout<<eat_weight<<" kg wheat (Carbonhydrate) eaten by beef cattle "<<_anml->getName()<<endl;
            cout<<"There is "<<food_weight_in_plate<< " kg wheat left in plate "<<endl;
            if(eat_weight <= 1.0){
                cout<<"Cattle eat too few it may be sick!!"<<endl;
            }
        }
        else{
            cout<<"There is not enough food in plate please prepare some more food "<<endl;
        }
    }
};

//Abstract Factory Class
class Food_Factory{
public:
    virtual Protein * createProteinFood() = 0;
    virtual Carbonhydrate * createCarbonhydrateFood() = 0;
};

//Concrete Factory Class1
class Milk_Cattle_Food_Factory : public Food_Factory{
private:
    Animal *_anml;
public:
    Milk_Cattle_Food_Factory(Animal *anml) : _anml(anml){};
    Protein * createProteinFood(){
        return new Soybean(_anml);
    }
    Carbonhydrate * createCarbonhydrateFood(){
        return new Corn(_anml);
    }
};

//Concrete Factory Class2
class Beef_Cattle_Food_Factory : public Food_Factory{
private:
    Animal *_anml;
public:
    Beef_Cattle_Food_Factory(Animal * anml) : _anml(anml){};
    Protein * createProteinFood(){
        return new Canola(_anml);
    }
    Carbonhydrate * createCarbonhydrateFood(){
        return new Wheat(_anml);
    }
};

//My Client Class
class Hungry_Cattles_Wants_Food{
public:
    void createFood(Food_Factory *food){
        proteins = food -> createProteinFood();
        carbonhydrates = food -> createCarbonhydrateFood();
    }
    Protein *getProteins(){return proteins;}
    Carbonhydrate *getCarbonhydrates(){return carbonhydrates;}
private:
    Protein *proteins;
    Carbonhydrate *carbonhydrates;
};

//AbstractObserver
class Observer{
public:
    virtual ~Observer(){};
    virtual void update(Animal & animal) = 0;
};

//ConcreteObserver1
class ZigbeeTracker : public Observer{
private:
    Animal anml;
    string tracker_name;
    string cattle_name;
    double cattle_loc_x;
    double cattle_loc_y;

public:

    ZigbeeTracker(string name) : tracker_name(name) {};

    //Updates the location informations for zigbee tracker and notify.
    void update(Animal & animal){
        anml = animal;
        cattle_name = animal.getName();
        cattle_loc_x = animal.getLocation_x();
        cattle_loc_y = animal.getLocation_y();
        cout << cattle_name << " exit the farm boundaries Current Location of cattle X:" << cattle_loc_x << " - Y:" << cattle_loc_y <<endl;
        cout<<"Data send via zigbee signal !! "<<endl;
    }

    //Informaiton Which To Send Central Receiver
    void InfoToSendToReceiver_Zigbee(){
        cout<<"Data send via zigbee signal !! "<<endl;
    }

    void setAnimal(Animal _animal){
        anml = _animal;
    }

    Animal getAnimal(){
        return anml;
    }

    string getName(){
        return tracker_name;
    }
};

//ConcreteObserver2
class BluetoothTracker : public Observer{
private:
    Animal anml;
    string tracker_name;
    string cattle_name;
    double cattle_loc_x;
    double cattle_loc_y;

public:

    BluetoothTracker(string name) : tracker_name(name) {};
    BluetoothTracker(){};

    //Updates the location informations for zigbee tracker and notify.
    void update(Animal & animal){
        anml = animal;
        cattle_name = animal.getName();
        cattle_loc_x = animal.getLocation_x();
        cattle_loc_y = animal.getLocation_y();
        cout << cattle_name << " exit the farm boundaries Current Location of cattle X:" << cattle_loc_x << " - Y:" << cattle_loc_y << "\n";
    }

    //Informaiton Which To Send Central Receiver
    virtual void InfoToSendToReceiver_Bluetooth() = 0;

    void setAnimal(Animal _animal){
        anml = _animal;
    }

    Animal getAnimal(){
        return anml;
    }

    string getName(){
        return tracker_name;
    }
};


//This Is Our Adapter Class For The Adapt Bluetooth Signals To Zigbee Signals
class Bluetooth_ZigbeeAdapter : public BluetoothTracker{
public:
    void InfoToSendToReceiver_Bluetooth(){
        cout<<"Signal Successfully Adapted Zigbee from Bluetooth For Send to Zigbee Receiver "<<endl;
        //Calling InfoToSendToReceiver_Zigbee() method from zigbee
        _zgb -> InfoToSendToReceiver_Zigbee();
    }

    Bluetooth_ZigbeeAdapter(ZigbeeTracker *zgb) : _zgb(zgb) {};

private:
    ZigbeeTracker *_zgb;
    string _trackerName;
};

//Attach Zigbee Tracker to animal
void Animal::attachZigbeeTracker(ZigbeeTracker *trc , Animal *anml){
    cout<<"Attached a tracker to the "<< anml->getName()<<endl;
    ZigbeeTrackers.push_back(trc);
}

//Detach Zigbee Tracker from animal
void Animal::detachZigbeeTracker(ZigbeeTracker *trc , Animal *anml){

    cout<<"The tracker has removed from the cattle "<< anml->getName()<<endl;

    for (unsigned int i= 0; i< ZigbeeTrackers.size(); i++) {
		if (ZigbeeTrackers[i]->getName() == trc->getName()) {
			ZigbeeTrackers.erase(ZigbeeTrackers.begin()+i);
			return;
		}
    }
}


//Attach Bluetooth Tracker to animal
void Animal::attachBluetoothTracker(BluetoothTracker *trc , Animal *anml){
    cout<<"Attached a tracker to the "<< anml->getName() <<endl;
    BluetoothTrackers.push_back(trc);
}

//Detach bluetooth Tracker from animal
void Animal::detachBluetoothTracker(BluetoothTracker *trc , Animal *anml){

    cout<<"The tracker has removed from the cattle "<< anml->getName() <<endl;

    for (unsigned int i= 0; i< BluetoothTrackers.size(); i++) {
		if (BluetoothTrackers[i]->getName() == trc->getName()) {
			BluetoothTrackers.erase(BluetoothTrackers.begin()+i);
			return;
		}
    }
}

//Notify Trackers
void Animal::notify(){
    for (unsigned int i = 0; i < ZigbeeTrackers.size(); i++) {
        //Calling the update method for each concrete observer to notify observers
		ZigbeeTrackers[i] -> update(*this);
	}
	for (unsigned int i = 0; i < BluetoothTrackers.size(); i++) {
	    //Calling the update method for each concrete observer to notify observers
		BluetoothTrackers[i] -> update(*this);
	}
}

int main(){

    ZigbeeTracker* trc_1 = new ZigbeeTracker("Tracker_1");
    ZigbeeTracker* trc_2 = new ZigbeeTracker("Tracker_2");
    ZigbeeTracker* trc_3 = new ZigbeeTracker("Tracker_3");
    BluetoothTracker * trc_4 = new Bluetooth_ZigbeeAdapter(new ZigbeeTracker("Tracker_4"));

       Beef_Cattle* b_cattle1 = new Beef_Cattle("SariKiz", 50.0 , 20.0);
       Beef_Cattle* b_cattle2 = new Beef_Cattle("KocaBas", 30.0 , 45.0);
       Milk_Cattle* m_cattle1 = new Milk_Cattle("Kinali", 39.0 , 41.0);
       Milk_Cattle* m_cattle2 = new Milk_Cattle("Kuheylan", 33.5 , 32.0);

       b_cattle1->attachZigbeeTracker(trc_1,b_cattle1);
       b_cattle2->attachZigbeeTracker(trc_2,b_cattle2);
       m_cattle1->attachZigbeeTracker(trc_3,m_cattle1);
       m_cattle2->attachBluetoothTracker(trc_4,m_cattle2);

       cout<<endl;

       b_cattle1->setLocation(200.10 , -10.0);
       b_cattle2->setLocation(-120.75 , -97.0);
       m_cattle1->setLocation(-330.75 , -97.0);
       m_cattle2->setLocation(-480.75 , -117.0);
       trc_4->InfoToSendToReceiver_Bluetooth();

       cout<<endl;

       b_cattle1->setLocation(-322.43 , 300.0);
       b_cattle2->setLocation(60.52 , 30.10);
       m_cattle1->setLocation(-45.75 , -97.85);
       m_cattle2->setLocation(-330.75 , -97.0);
       trc_4->InfoToSendToReceiver_Bluetooth();

       cout<<endl;

       Food_Factory *_milk_cattle_food = new Milk_Cattle_Food_Factory(m_cattle1);
       Food_Factory *_beef_cattle_food = new Beef_Cattle_Food_Factory(b_cattle1);
       Food_Factory *_milk_cattle_food2 = new Milk_Cattle_Food_Factory(m_cattle2);
       Food_Factory *_beef_cattle_food2 = new Beef_Cattle_Food_Factory(b_cattle2);

       Hungry_Cattles_Wants_Food _hcwf;

       _hcwf.createFood(_milk_cattle_food);

       Protein *_pro = _hcwf.getProteins();
       Carbonhydrate *_crb = _hcwf.getCarbonhydrates();

       cout<<endl;

       _pro->prepareFood(2.5);
       _pro->eatFood(1.0);

       cout<<endl;

       _crb->prepareFood(2.5);
       _crb->eatFood(2.3);

       cout<<endl;

       _hcwf.createFood(_beef_cattle_food);

       Protein *_pro2 = _hcwf.getProteins();
       Carbonhydrate *_crb2 = _hcwf.getCarbonhydrates();

       cout<<endl;

       _pro2->prepareFood(2.5);
       _pro2->eatFood(1.8);

       cout<<endl;

       _crb2->prepareFood(2.5);
       _crb2->eatFood(1.3);

       cout<<endl;

       _hcwf.createFood(_milk_cattle_food2);

       Protein *_pro3 = _hcwf.getProteins();
       Carbonhydrate *_crb3 = _hcwf.getCarbonhydrates();

       cout<<endl;

       _pro3->prepareFood(2.5);
       _pro3->eatFood(1.4);

       cout<<endl;

       _crb3->prepareFood(2.5);
       _crb3->eatFood(2.5);

       cout<<endl;

       _hcwf.createFood(_beef_cattle_food2);

       Protein *_pro4 = _hcwf.getProteins();
       Carbonhydrate *_crb4 = _hcwf.getCarbonhydrates();

       cout<<endl;

       _pro4->prepareFood(2.5);
       _pro4->eatFood(0.9);

       cout<<endl;

       _crb4->prepareFood(2.5);
       _crb4->eatFood(2.2);

       cout<<endl;

       Veterinary *vet = new Veterinary();
       Ministry_Inspector *ins = new Ministry_Inspector();
       Cattles *cattle = new Cattles();

       cattle->Add(b_cattle1);
       cattle->Add(b_cattle2);
       cattle->Add(m_cattle1);
       cattle->Add(m_cattle2);

       cattle->Accept(vet);

       cout<<endl;

       cattle->Accept(ins);

return 0;
}
