import { defineCollection, z } from 'astro:content';

const projectsCollection = defineCollection({
  type: 'data',
  schema: z.object({
    title: z.string(),
    dropdownTitle: z.string().optional(),
    description: z.string(),
    briefDescription: z.string(),
    skills: z.array(z.string()),
    technologies: z.array(z.string()),
    image: z.string(),
    demoUrl: z.string().optional(),
    repositoryUrl: z.string().optional(),
    featured: z.boolean().optional(),
    additionalInfo: z.record(z.string()).optional(),
    order: z.number().optional().default(0),
    sections: z.array(
      z.object({
        title: z.string(),
        content: z.string().optional(),
        listItems: z.array(z.string()).optional().default([]),
        image: z.string().optional(),
        videoUrl: z.string().optional()
      })
    ).optional().default([])
  })
});

const aboutCollection = defineCollection({
    type: 'data',
    schema: z.object({
      title: z.string(),
      subtitle: z.string(),
      intro: z.string(),
      heroText: z.string(),
      shortBio: z.string().transform((str) =>
        str.replace(/\*\*(.*?)\*\*/g, "<strong>$1</strong>")),
      skills: z.array(z.string()),
      contacts: z.object({
        email: z.string(),
        github: z.string().optional(),
        linkedin: z.string().optional(),
        itchio: z.string().optional()
      }),
      featuredImage: z.string().optional()
    })
  });

  console.log(aboutCollection)

export const collections = {
  projects: projectsCollection,
  about: aboutCollection
};
