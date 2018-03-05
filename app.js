var Person={name:"phodal",weight:50,height:166};
function dream(){
    future;
};
Person.future=dream;
document.write(typeof Person);
document.write(Person.future+"<br>");
//等价代码
var Person=function(){
    this.name="phodal";
    this.weight=50;
    this.height=166;
    this.future=function dream(){
        return "future";
    };
};
var person=new Person();
document.write(person.name+"<br>");
document.write(typeof person+"<br>");
document.write(typeof person.future+"<br>");
document.write(person.future+"<br>");


var Chinese=function(){
	this.country="China";
}

Chinese.prototype = new Person();

var phodal = new Chinese("phodal", 50, 166);
//document.write(phodal.country+"<br>");
//继承机制
document.write(phodal.name)
var para=document.getElementById("para");
para.style.color="blue";