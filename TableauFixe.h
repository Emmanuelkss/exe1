//
// Created by emman on 2026-09-17.
//

#ifndef EXE1_TABLEAUFIXE_H
#define EXE1_TABLEAUFIXE_H

#include <stdexcept>

template <typename Element>
class TableauFixe {

public:
    TableauFixe();
    explicit TableauFixe(int n);
    TableauFixe(const TableauFixe& source);
    TableauFixe(TableauFixe&& source) noexcept;
    ~TableauFixe();

    TableauFixe& operator=(const TableauFixe& source);
    TableauFixe& operator=(TableauFixe&& source) noexcept;


    int taille() const;
    bool estVide() const;

    Element& operator[](int i);
    const Element& operator[](int i) const;

    Element& element(int i);
    const Element& element(int i) const;

    Element& premier();
    const Element& premier() const;
    Element& dernier();
    const Element& dernier() const;

    void remplis(const Element& valeur);
    void echange(TableauFixe& autre) noexcept;

    TableauFixe fusion(const TableauFixe& autre) const;

    template <int M>
    TableauFixe<Element> sousEnsemble(int debut) const;

private:
    Element* donnees;
    int n;

    bool indiceValide(int i) const;
};


// Implémentation

template <typename Element>
TableauFixe<Element>::TableauFixe() : TableauFixe(0) {
}

template <typename Element>
TableauFixe<Element>::TableauFixe(int n) : donnees(new Element[n]), n(n) {
}

template <typename Element>
TableauFixe<Element>::TableauFixe(const TableauFixe& source)
    : donnees(new Element[source.n]), n(source.n) {
    for (int i = 0; i < n; ++i) {
        donnees[i] = source.donnees[i];
    }
}

template <typename Element>
TableauFixe<Element>::TableauFixe(TableauFixe&& source) noexcept
    : donnees(source.donnees), n(source.n) {
    source.donnees = nullptr;
    source.n = 0;
}

template <typename Element>
TableauFixe<Element>::~TableauFixe() {
    delete[] donnees;
}

template <typename Element>
TableauFixe<Element>& TableauFixe<Element>::operator=(const TableauFixe& source) {
    if (this != &source) {
        Element* nouvelles = new Element[source.n];
        for (int i = 0; i < source.n; ++i) {
            nouvelles[i] = source.donnees[i];
        }
        delete[] donnees;
        donnees = nouvelles;
        n = source.n;
    }
    return *this;
}

template <typename Element>
TableauFixe<Element>& TableauFixe<Element>::operator=(TableauFixe&& source) noexcept {
    if (this != &source) {
        delete[] donnees;
        donnees = source.donnees;
        n = source.n;
        source.donnees = nullptr;
        source.n = 0;
    }
    return *this;
}

template <typename Element>
int TableauFixe<Element>::taille() const {
    return n;
}

template <typename Element>
bool TableauFixe<Element>::estVide() const {
    return n == 0;
}

template <typename Element>
const Element& TableauFixe<Element>::operator[](int i) const {
    return donnees[i];
}

template <typename Element>
Element& TableauFixe<Element>::operator[](int i) {
    return const_cast<Element&>(static_cast<const TableauFixe&>(*this)[i]);
}

template <typename Element>
const Element& TableauFixe<Element>::element(int i) const {
    if (!indiceValide(i)) {
        throw std::out_of_range("TableauFixe::element : indice hors bornes");
    }
    return donnees[i];
}

template <typename Element>
Element& TableauFixe<Element>::element(int i) {
    return const_cast<Element&>(static_cast<const TableauFixe&>(*this).element(i));
}

template <typename Element>
const Element& TableauFixe<Element>::premier() const {
    return donnees[0];
}

template <typename Element>
Element& TableauFixe<Element>::premier() {
    return const_cast<Element&>(static_cast<const TableauFixe&>(*this).premier());
}

template <typename Element>
const Element& TableauFixe<Element>::dernier() const {
    return donnees[n - 1];
}

template <typename Element>
Element& TableauFixe<Element>::dernier() {
    return const_cast<Element&>(static_cast<const TableauFixe&>(*this).dernier());
}

template <typename Element>
void TableauFixe<Element>::remplis(const Element& valeur) {
    for (int i = 0; i < n; ++i) {
        donnees[i] = valeur;
    }
}

template <typename Element>
void TableauFixe<Element>::echange(TableauFixe& autre) noexcept {
    Element* tempDonnees = donnees;
    donnees = autre.donnees;
    autre.donnees = tempDonnees;

    int tempN = n;
    n = autre.n;
    autre.n = tempN;
}

template <typename Element>
TableauFixe<Element> TableauFixe<Element>::fusion(const TableauFixe& autre) const {
    TableauFixe<Element> resultat(n + autre.n);
    for (int i = 0; i < n; ++i) {
        resultat.donnees[i] = donnees[i];
    }
    for (int i = 0; i < autre.n; ++i) {
        resultat.donnees[n + i] = autre.donnees[i];
    }
    return resultat;
}

template <typename Element>
template <int M>
TableauFixe<Element> TableauFixe<Element>::sousEnsemble(int debut) const {
    TableauFixe<Element> resultat(M);
    for (int i = 0; i < M; ++i) {
        resultat.donnees[i] = donnees[debut + i];
    }
    return resultat;
}

template <typename Element>
bool TableauFixe<Element>::indiceValide(int i) const {
    return i >= 0 && i < n;
}

#endif //EXE1_TABLEAUFIXE_H