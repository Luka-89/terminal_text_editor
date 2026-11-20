#include <Kuca.h>

Kuca::Kuca() {};


void Kuca::dodaj(std::unique_ptr<Uredjaj> u) {
    uredjaji.push_back(std::move(u));
}

bool Kuca::ukloni(int id) {
    for(int i = 0; i < uredjaji.size(); i++) {
        if(uredjaji[i].get()->getId() == id) {
            uredjaji.erase(uredjaji.begin() + i);
        }
    }
    uredjaji.erase(uredjaji.begin() + id);
}

Uredjaj* Kuca::nadji(int id) const {
    for(int i = 0; i < uredjaji.size(); i++) {
        if(uredjaji[i].get()->getId() == id) {
            return uredjaji[i].get();
        }
    }
    return nullptr;
}