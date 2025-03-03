import { defineCollection, z } from 'astro:content';

const projectsCollection = defineCollection({
  type: 'data',
  schema: z.object({
    title: z.string(),
    description: z.string(),
    technologies: z.array(z.string()),
    image: z.string(),
    demoUrl: z.string().optional(),
    repositoryUrl: z.string().optional(),
    featured: z.boolean().optional(),
    sections: z.array(
      z.object({
        title: z.string(),
        content: z.string(),
        listItems: z.array(z.string()).optional().default([]),
        // Rendi l'immagine opzionale
        image: z.string().optional(),
        // Aggiungi un campo opzionale per il video
        videoUrl: z.string().optional()
      })
    ).optional().default([])
  })
});

export const collections = {
  'projects': projectsCollection
};
