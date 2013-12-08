package com.simpleservlets;


import javax.xml.bind.annotation.XmlRootElement;

@XmlRootElement
public class Simple {
    private int a;

    public Simple() {
    }

    public Simple(int a) {
        this.a = a;
    }

    public int getA() {
        return a;
    }

    public void setA(int a) {
        this.a = a;
    }
}
