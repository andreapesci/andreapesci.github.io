from typing import Optional, List
from pydantic import BaseModel

class Post(BaseModel):
    id: str
    title: str
    description: str
    cover: str
    tags: Optional[str] = None
    category: Optional[str] = None