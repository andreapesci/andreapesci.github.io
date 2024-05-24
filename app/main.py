from fastapi import FastAPI, Request
from fastapi.responses import HTMLResponse
from fastapi.staticfiles import StaticFiles
from fastapi.templating import Jinja2Templates

app = FastAPI()

app.mount("/static", StaticFiles(directory="app/static"), name="static")

templates = Jinja2Templates(directory="app/templates")

@app.get("/", response_class=HTMLResponse)
async def read_root(request: Request):
    return templates.TemplateResponse("index.html", {"request": request})

@app.get("/resume", response_class=HTMLResponse)
async def read_about(request: Request):
    return templates.TemplateResponse("resume.html", {"request": request})

@app.get("/home", response_class=HTMLResponse)
async def read_contact(request: Request):
    return templates.TemplateResponse("home.html", {"request": request})



@app.get("/hello", response_class=HTMLResponse)
async def say_hello(request: Request):
    return HTMLResponse("<div id='message'>Hello from FastAPI!</div>")
