console.log("hi!!");

const button = document.getElementById("postButton");
button.addEventListener("click", executeUpload);
const req = new XMLHttpRequest();

req.onload=function(evt){
        
    alert(req.responseText);
}

req.onerror=function(){
    alert('failed to upload.\n');
}

req.upload.onprogress=function(evt){
    let progVal = (evt.loaded / evt.total * 100).toFixed(1);
    progressBar.value = progVal;
    progressInformation.innerHTML = progVal + '%';
}

function executeUpload(evt){
    const title = document.getElementById("title");
    const detail = document.getElementById("detail");
    const medias_choose = document.getElementsByClassName("media_choose");
    const github = document.getElementById("github");
    const zip_file = document.getElementById("zipFile").files[0];
    
    let formData = new FormData();
    // formData.append("title", title);
    // formData.append("detail", detail);
    // for(let i = 0; i < 5; i++){
    //     formData.append("media_" + i, medias_choose[i].files[0]);
    // }
    // formData.append("github", github);
    formData.append("zip", zip_file);

    fetch(".", {method: "POST", body: formData});
    // req.open("POST", "", true);
    // req.send(formData);
}