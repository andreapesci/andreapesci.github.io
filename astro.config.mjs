// @ts-check
import { defineConfig } from 'astro/config';
import mdx from "@astrojs/mdx";
import react from '@astrojs/react';


// https://astro.build/config
export default defineConfig({
  output: 'static',
  site: 'https://andreapesci.com',
  trailingSlash: 'never',
  integrations: [mdx(), react()],
  build: {
    format: 'directory',
  },
  vite: {
    ssr: {
      noExternal: ['astro-transitions'],
    },
  },
  prefetch: {
    prefetchAll: true,
    defaultStrategy: 'hover'
  },
});
