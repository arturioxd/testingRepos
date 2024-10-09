#include <iostream>
#include <memory>
#include <string>

class Phone {
public:
    virtual std::string getModel() const = 0;
    virtual double getPrice() const = 0;
    virtual int getDeliveryTime() const = 0;
    virtual ~Phone() {}
};

class USAPhone : public Phone {
public:
    std::string getModel() const override {
        return "������ ���";
    }
    double getPrice() const override {
        return 1000; 
    }
    int getDeliveryTime() const override {
        return 7;
    }
};

class EastCountryPhone : public Phone {
public:
    std::string getModel() const override {
        return "������ �����";
    }
    double getPrice() const override {
        return 700;
    }
    int getDeliveryTime() const override {
        return 14;
    }
};

class PhoneFactory {
public:
    virtual std::shared_ptr<Phone> createPhone() const = 0;
    virtual ~PhoneFactory() {}
};

class USAFactory : public PhoneFactory {
public:
    std::shared_ptr<Phone> createPhone() const override {
        return std::make_shared<USAPhone>();
    }
};

class EastCountryFactory : public PhoneFactory {
public:
    std::shared_ptr<Phone> createPhone() const override {
        return std::make_shared<EastCountryPhone>();
    }
};

class OnlineStore {
public:
    OnlineStore(std::shared_ptr<PhoneFactory> factory) : factory(factory) {}

    void orderPhone() const {
        auto phone = factory->createPhone();
        std::cout << "������: " << phone->getModel() << std::endl;
        std::cout << "ֳ��: $" << phone->getPrice() << std::endl;
        std::cout << "��� ��������: " << phone->getDeliveryTime() << " ���" << std::endl;
    }

private:
    std::shared_ptr<PhoneFactory> factory;
};

int main() {
    setlocale(LC_ALL, "Ukrainian");
    int choice;
    std::cout << "�����-��������:\n1. ���\n2. ����� �����" << std::endl;
    std::cin >> choice;

    std::shared_ptr<PhoneFactory> factory;

    if (choice == 1) {
        factory = std::make_shared<USAFactory>();
    }
    else if (choice == 2) {
        factory = std::make_shared<EastCountryFactory>();
    }
    else {
        std::cout << "������������ ����!" << std::endl;
        return 1;
    }

    OnlineStore store(factory);
    store.orderPhone();

    return 0;
}
