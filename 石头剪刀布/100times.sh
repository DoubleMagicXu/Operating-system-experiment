#!/bin/bash
for((i=0;i<100;i++))
{
    ./player01&
    ./player02&
    ./referee
}
