async function f()
{
    try {
        let res=await fetch('');
        let x=res.json();
    } catch (error) {
        console.log(error);
    }
}

f();