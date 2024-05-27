from fastapi import FastAPI, Request
from fastapi.responses import HTMLResponse
from fastapi.staticfiles import StaticFiles
from jinja2_fragments.fastapi import Jinja2Blocks
import jinja_partials

from app.services.portfolio_service import all_projects
from app.services.blog_service import all_blogs

app = FastAPI()

app.mount("/static", StaticFiles(directory="app/static"), name="static")

templates = Jinja2Blocks(directory="app/templates")

jinja_partials.register_starlette_extensions(templates)

@app.get("/", response_class=HTMLResponse)
async def read_root(request: Request):
    portfolio = all_projects()
    blog = all_blogs()
    return templates.TemplateResponse("home/index.html", {"request": request, "portfolio": portfolio, "blog":blog})

@app.get("/resume", response_class=HTMLResponse)
async def read_about(request: Request):
    return templates.TemplateResponse("resume.html", {"request": request})

@app.get("/home", response_class=HTMLResponse)
async def read_contact(request: Request):
    portfolio = all_projects()
    blog = all_blogs()
    return templates.TemplateResponse("home/index.html", {"request": request, "portfolio": portfolio, "blog":blog})

